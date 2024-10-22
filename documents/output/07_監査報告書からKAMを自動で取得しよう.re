= 監査報告書からKAMを自動で取得しよう

== 本章の目的

本章では今までと少し異なり、有価証券報告書の添付書類である監査報告書という書類からデータを取得します。

具体的にはKAMという指標を取得します。KAMは「当年度の財務諸表の監査において、監査人が職業的専門家として特に重要であると判断した事項」です。しかし、KAMは会計士などでない限りあまり知られていないものです。本章では、監査報告書とKAMが何かを説明したうえでデータを取得できるようなることを目指します。

== 監査報告書とKAMについて

KAMとは「当年度の財務諸表の監査において、監査人が職業的専門家として特に重要であると判断した事項」をまとめた項目であり、監査報告書はこのKAMや監査人の名前など監査に関わる事項が記載されている書類です。

監査をする会計士以外の多くの人は監査報告書やKAMがわからない方も多いと思います。この2つについてもう少し詳しく知った上でデータを取得しましょう。

=== 監査報告書とは

監査報告書は日本会計士協会によると以下のような書類だと定められています。

//quote{
経営者の作成した財務諸表が、一般に公正妥当と認められる企業会計の基準に準拠して、企業の財政状態、経営成績及びキャッシュ・フローの状況をすべての重要な点において適正に表示しているかどうかについて監査人の監査意見を述べた報告書である。出典：@<href>{https://jicpa.or.jp/cpainfo/introduction/keyword/post-77.html,日本会計士協会 監査報告書}
//}

簡単に言うと、「財務諸表の専門家である公認会計士が適正と認めるもの」です。内容として監査を担当した会計士の名前や監査意見、その根拠などが書いてあります。そのため、世の中に提出されたすべての有価証券報告書に対しこの監査報告書は添付されています。

また提出本文書と違う点として、連結と個別で書類ごと分かれています。

以下がEDIENTで見たときの監査報告書です。上部のタブから「監査報告書」を選択すると閲覧できます。監査報告書には連結と個別が別のファイルになっていることが確認できます。

//image[images\0701_監査報告書の例][監査報告書の例（2023年度トヨタ自動車株式会社）]{
//}

=== KAMとは

KAM（カム）は「監査上の主要な検討事項」（Key Audit Matters）の略称です。金融庁によるとKAMは以下のようなものだと言います。

//quote{
監査人が実施した監査の透明性を向上させ監査報告書の情報価値を高めることにその意義がある。出典：@<href>{https://www.fsa.go.jp/news/r3/sonota/20220304-2/20220304-2.html,金融庁　「監査上の主要な検討事項（KAM）の特徴的な事例と記載のポイント」の公表}
//}

KAMは財務情報などと比べると参照されるケースは少ないですが、財務諸表の監査において特に重要なことが書かれています。そのため、監査報告書の中では重要視されることが多いです。また、企業・事業ごとで業務の体系・詳細は変わってくるため、それらをどう監査のルールに当てはめるのかなどが書かれています。他にも内容だけでなく、表の見出しも企業や年度によっても異なるため、見出しの中にどんな単語が多いのかなど分析ができるのが特徴です。

@<embed>{|html|<img width=450 alt="KAMの例1" src="images\0702_KAMの例_1.png">}

@<embed>{|html|<img width=450 alt="KAMの例2" src="images\0703_KAMの例2.png">}

例）トヨタ自動車2023年度のKAM

== 監査報告書からKAMを自動で取得する

監査報告書とKAMがどのようなものなのか分かったところで、実際にデータを取得してみましょう。

=== タクソノミを確認しよう

本章でも情報を取得するために、タクソノミを確認します。

今回は2章で紹介したタクソノミの参照方法の3つ目である、「金融庁のタクソノミ要素リスト」を使用してタクソノミを参照します。理由としてはKAMは標準タクソノミというどの有報にも必ず存在するタクソノミだからです。標準タクソノミは金融庁から提出されているタクソノミ要素リストから確認することができます。タクソノミ要素リストからの参照方法は、標準タクソノミを調べる際は一番見つかりやすい参照方法です。ただし、情報が多すぎてどこを探したらいいのかわからなかったり、たまに間違ったりもするため注意が必要です。

タクソノミ要素リストは以下のURLからダウンロードができます。

https://www.fsa.go.jp/search/20231211/1e_ElementList.xlsx

（1）目次から「9 企業内容等の開示に関する内閣府令 第三号様式 有価証券報告書(jpcrp03000-asr)」のシートを選択

//image[images\0704_タクソノミ要素リストの目次][タクソノミ要素リスト目次]{
//}

（2）「Ctrl」＋「F」で検索窓から「監査上の主要な検討事項」と検索（3）「詳細ツリー‐標準ラベル（日本語）」（B列）でヒットするものを探す

//image[images\0705_タクソノミ要素リスト内で目的の項目を検索][タクソノミ要素リスト内で検索]{
//}

（4）「冗長ラベル（日本語）」（C列）で連結のものと個別のものが分かれていることが確認できるため連結のものの「要素名」（I列）を確認

//image[images\0706_タクソノミ要素リストの中から参照する][タクソノミ要素リストから参照]{
//}

これをkeyとして使用します。

注意点として、連結と個別のファイルがそれぞれあります。連結のKAMを抽出したいため、タグは"KeyAuditMattersConsolidatedTextBlock"です。

今回は今までとは異なり、タグが「：」で分かれていないためExcelファイルの I列目である要素名だけ指定しましょう。

context_refに関しては財務情報と異なり、当期のものしかないため"FilingDateInstant"と指定します。

以上の2つをメモします。

=== 取得するコードを書こう

大枠は前章までと変わりませんので、異なる点をメインに説明します。

KAMは有価証券報告書の提出本文書ではなく監査報告書にのみ記載されている内容のため、有報のパスだけでなく、監査報告書のパスも通します。

今まで参照していた有報の中の提出本文書類を示すものが「PublicDoc」です。今回は監査報告書の中からデータを取得したいため、パスを通すときに「AuditDoc」と指定します。

//table{
EDINETから見たときの名称	フォルダを開いたときの名称
--------------
提出本文書類	PublicDoc
監査報告書	AuditDoc
//}

監査報告書の連結と個別の区別はファイル単位で分かれているため、正規表現を使用しても正しくファイルを指定できるようにしていきます。

EDINETからダウンロードした監査報告書のファイル名には略号というものがあり、これを活用していきます。

//table{
独立監査人の報告書	@<dtp>{table align=center}略号	基本的な会計のドメイン知識
--------------
監査報告書及び内部統制監査報告書	@<dtp>{table align=center}aai	連結の情報が載っている
監査報告書	@<dtp>{table align=center}aar	個別の情報が載っている
//}

本章では、連結の情報を取得します。連結のデータが存在する「aai」のファイルを指定します。

//image[images\0707_タクソノミ連結個別の指定][タクソノミで連結・個別の指定をする]{
//}

aaiがある場所は AuditDoc と .xbrl の間です。正規表現を用いてここにaaiが載っているファイルを指定し過不足なくデータを取得できます。指定ができたらcompany_infoに両方のファイルを入れます。

//emlist[][python]{
def main():
    xbrl_files = glob.glob(r'*フォルダ名\*\XBRL\PublicDoc\*.xbrl')
    audit_files = glob.glob(r'*フォルダ名\*\XBRL\AuditDoc\*aai*.xbrl')

    company_info = make_edinet_company_info_list(xbrl_files, audit_files)
//}

ファイルを読み込む部分でもaudit_filesを読み込みます。zipを使用し、有報のデータと監査報告書のデータが一組にします。

//emlist[][python]{
for index, (xbrl_file, audit_file) in enumerate(zip(xbrl_files, audit_files)):
        company_data = {
            "EDINETCODE": "",
            "企業名": "",
            "KAM": "",
        }

        # (コントローラーの設定などは省略)

        model_xbrl = model_manager.load(xbrl_file)
        model_audit = model_manager.load(audit_file)
//}

EDIENTコードと企業名は有報から取得し、KAMは監査報告書から取得しています。

if文の中でタクソノミを指定します。KAMはテキストデータであるためデータクレンジングをします。

データは最後にリストで保管します。最後に保管せずにEDIENTコードと企業名を見つけた段階でリストに入れてしまうと別のリストとして保管してしまいます。別のリストで保管すると、企業名とKAMが別々になり思うように利用できないデータになってしまう可能性があります。

//emlist[][python]{
# 監査データからKAMを探して取得
for fact in model_audit.facts:

    # KAMを探す
    if fact.concept.qname.localName == 'KeyAuditMattersConsolidatedTextBlock':
        if fact.contextID == 'FilingDateInstant':
            company_data["KAM"] = fact.value

            # BeautifulSoupを使ってHTMLタグを除去
            soup = BeautifulSoup(company_data["KAM"], "html.parser")
            company_data["KAM"] = soup.get_text()

            # 空白や改行を取り除く
            company_data["KAM"] = re.sub(r'\s', '', company_data["KAM"]).strip()

# 見つけたデータをリストに入れる
        edinet_company_info_list.append([
            company_data["EDINETCODE"],
            company_data["企業名"],
            company_data["KAM"],
        ])
//}

以下がすべてをまとめたソースコードになります。

=== ソースコード

//emlist[][python]{
from arelle import ModelManager
from arelle import Cntlr
import os
import glob
import re
from bs4 import BeautifulSoup

def make_edinet_company_info_list(xbrl_files, audit_files):
    edinet_company_info_list = []
    for index, (xbrl_file, audit_file) in enumerate(zip(xbrl_files, audit_files)):
        company_data = {
            "EDINETCODE": "",
            "企業名": "",
            "KAM": "",
        }

        ctrl = Cntlr.Cntlr()
        model_manager = ModelManager.initialize(ctrl)

        model_xbrl = model_manager.load(xbrl_file)
        model_audit = model_manager.load(audit_file)
        print("XBRLファイルを読み込んでいます", ":", index + 1, "/", len(xbrl_files))

        # 実データを探して取得
        for fact in model_xbrl.facts:

            # EDINETコードを探す
            if fact.concept.qname.localName == 'EDINETCodeDEI':
                company_data["EDINETCODE"] = fact.value

            # 企業名を探す
            elif fact.concept.qname.localName == 'FilerNameInJapaneseDEI':
                company_data["企業名"] = fact.value

        # 監査データからKAMを探して取得
        for fact in model_audit.facts:

            # KAMを探す
            if fact.concept.qname.localName == 'KeyAuditMattersConsolidatedTextBlock':
                if fact.contextID == 'FilingDateInstant':
                    company_data["KAM"] = fact.value

                    # BeautifulSoupを使ってHTMLタグを除去
                    soup = BeautifulSoup(company_data["KAM"], "html.parser")
                    company_data["KAM"] = soup.get_text()

                    # 空白や改行を取り除く
                    company_data["KAM"] = re.sub(r'\s', '', company_data["KAM"]).strip()

        # 見つけたデータをリストに入れる
        edinet_company_info_list.append([
            company_data["EDINETCODE"],
            company_data["企業名"],
            company_data["KAM"],
        ])

    return edinet_company_info_list

def main():
    xbrl_files = glob.glob(r'*フォルダ名\*\XBRL\PublicDoc\*.xbrl')
    audit_files = glob.glob(r'*フォルダ名\*\XBRL\\AuditDoc\*aai*.xbrl')

    company_info = make_edinet_company_info_list(xbrl_files, audit_files)
    for info in company_info:
        print(info)

    print("extract finish")

if __name__ == "__main__":
    main()

//}

== まとめ

本章では、監査報告書からKAMという監査をする上で注目した点などのデータを取得しました。普段見ることが多くない書類・項目ではありますが取得が確認できました。

次章では今まで取得したデータを一つのコードでまとめてExcel形式で出力するということをします。Excelで出力することによりターミナルで確認するよりも見やすく、二次利用もしやすくなると思います。
