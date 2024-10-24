= 有報からテキストデータを自動で取得しよう

== 本章の目的

本章では有価証券報告書からテキストデータを取得してみます。有価証券報告書は財務諸表に代表される財務データのみならず、現在の事業の状況や財務データが算出された背景などについて書かれたテキストデータがあります。こうしたことから、多くの研究者が有価証券報告書を用いたテキスト分析を実施しております。さらに、昨今のAIの発展などによりテキストデータの解析技術が向上し注目が高まっています。

== 有報から事業等のリスクだけを自動で取得しよう

今回取得するテキストデータの項目は、事業等のリスクと呼ばれる項目です。事業等のリスクには、企業の財政状態や経営状況及びキャッシュ・フローの状況等に重要な影響を与える可能性があると経営者が認識している主要なリスクについて記載がされています。企業ごとはもちろん、事業年度ごとにも記載内容が大きく変わることもある項目です。そのため注目度も高く、テキスト分析などがされやすい項目と言えます。

本章でも前章同様にトヨタ自動車株式会社を軸にした10社からデータの取得を試みます。

=== タクソノミを確認しよう

本章でも、前までと同様にタクソノミを確認することから始めます。

本章では、「XBRLファイル内で検索」でタクソノミを参照します。コードエディタ(本書ではVS Code)で直接XBRLファイルを開き、「Ctrl＋F」で事業等のリスクを検索します

テキストデータは財務データと異なり、XBRLファイル内で直接タグで囲まれて記述されているため、実際に検索にかけてタクソノミを調べることができます。

検索をかけ、ハイライトされている前後を確認すると以下のような部分が見つかると思います。

//emlist[code61][python]{
<jpcrp_cor:BusinessRisksTextBlock contextRef="FilingDateInstant">&lt;p style="page-break-before:always; line-height:0.75pt; width:100%; font-size:0.75pt;"&gt; &lt;/p&gt;
&lt;h3 class="smt_head2" style="font-family:&amp;apos;ＭＳ ゴシック&amp;apos;;"&gt;３ 【事業等のリスク】～（省略）
//}

この"jpcrp_cor:BusinessRisksTextBlock”がタグであり、"FilingDateInstant"がコンテキストIDとなります。

=== 取得するコードを書こう

大まかなコードの形は前章のものと変わりません。

取得する対象が財務データである「営業利益(IFRS)」からテキストデータである「事業等のリスク」に代わっているため、タクソノミを変える必要があります。

タクソノミを先ほど調べた以下のものに書き変えましょう。

タグ（要素ID）が ”BusinessRisksTextBlock”、コンテキストIDが ”FilingDateInstant”

タグの方はタクソノミを調べたもののうち「：」以降の「BusinessRiskTextBlock」のみを指定します。

//emlist[code62][python]{
if fact.concept.qname.localName == 'BusinessRisksTextBlock':
　　　　if fact.contextID == 'FilingDateInstant':
       company_data["事業等のリスク"] = fact.value
//}

今回はBeautifulSoupというライブラリとreモジュールの両方を使用してデータを綺麗にしています。2つを使用することでより綺麗な状態でデータを取得できます。

Web上の文章は綺麗に見せるためのHTMLタグという機械への命令がテキストデータに混在し、人間には読みづらいものとなっています。BeautifulSoupはこれを除去する役割を担っています。

reモジュールは書類ごとで空白や改行の量が違うこともあるため、データを集める時点で全て除去し統一する役割を担っています。

これらどちらか片方のみを使用しても似たようなことはできます。しかし、BeautifulSoupだけだと空白や改行がたくさん残ってしまう、reモジュールだけではBeautifulSoupほど高精度でタグやネストを処理できないといった問題が残ってしまいます。両者のライブラリを利用することで双方の弱点を補完し、綺麗に文章を取得することが可能になります。

//emlist[code63][python]{
# BeautifulSoupを使ってHTMLタグを除去
soup = BeautifulSoup(company_data["事業等のリスク"], "html.parser")
company_data["事業等のリスク"] = soup.get_text()

# 空白や改行を取り除く
company_data["事業等のリスク"] = re.sub(r'\s', '', company_data["事業等のリスク"]).strip()
//}

▼ソースコード

//emlist[64][python]{
from arelle import ModelManager
from arelle import Cntlr
import os
import glob
import re
from bs4 import BeautifulSoup

def make_edinet_company_info_list(xbrl_files):
    edinet_company_info_list = []
    for index, xbrl_file in enumerate(xbrl_files):
        company_data = {
            "EDINETCODE": "",
            "企業名": "",
            "事業等のリスク": "",
        }

        ctrl = Cntlr.Cntlr()
        model_manager = ModelManager.initialize(ctrl)

        model_xbrl = model_manager.load(xbrl_file)
        print("XBRLファイルを読み込んでいます", ":", index + 1, "/", len(xbrl_files))

        # 実データを探して取得
        for fact in model_xbrl.facts:

            #  EDINETコードを探す
            if fact.concept.qname.localName == 'EDINETCodeDEI':
                company_data["EDINETCODE"] = fact.value

            # 企業名を探す
            elif fact.concept.qname.localName == 'FilerNameInJapaneseDEI':
                company_data["企業名"] = fact.value

            # 事業等のリスクを探す
            elif fact.concept.qname.localName == 'BusinessRisksTextBlock': # タグは「：」以降の部分を指定
                if fact.contextID == 'FilingDateInstant':
                    company_data["事業等のリスク"] = fact.value

                    # BeautifulSoupを使ってHTMLタグを除去
                    soup = BeautifulSoup(company_data["事業等のリスク"], "html.parser")
                    company_data["事業等のリスク"] = soup.get_text()

                    # 空白や改行を取り除く
                    company_data["事業等のリスク"] = re.sub(r'\s', '', company_data["事業等のリスク"]).strip()

        # 見つけたデータをリストに入れる
        edinet_company_info_list.append([
            company_data["EDINETCODE"],
            company_data["企業名"],
            company_data["事業等のリスク"],
        ])

    return edinet_company_info_list

def main():
    # 各人のXBRLファイルのパス(ただコピーしても動きません)
    xbrl_files = glob.glob(r'*xbrl_zip\*\XBRL\PublicDoc\*.xbrl')

    company_info = make_edinet_company_info_list(xbrl_files)
    for info in company_info:
        print(info)

    print("extract finish")

if __name__ == "__main__":
    main()
//}

== まとめ

本章はテキストデータの取得について学びました。取得した事業等のリスクは有価証券報告書の中でも目にしやすい項目の1つでもある項目です。このように欲しいテキストデータのみを取得できると企業の比較や分析など様々な用途で便利に使用することができます。

次章は、有価証券報告書の提出本文書ではなく監査報告書という追加の書類から「監査上の主要な検討事項（KAM）」という項目を抽出します。
