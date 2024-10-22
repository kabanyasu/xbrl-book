= CSVファイルで出力しよう

== 本章の目的

本章では、前章までで集めた個々のデータをまとめてCSVファイルで出力する方法を解説します。CSVファイルでデータ出力すれば、XBRLからデータを都度ダウンロードしなくても、ExcelやPythonなどを用いてEDINETから出力したデータを参照できるようになります。

今回は、今まで取得してきたデータに「業種」を加えた以下の6項目をカラムに設定します。

 * EDINETコード
 * 企業名
 * 業種
 * 営業利益(IFRS)
 * 事業等のリスク
 * KAM

今回はEDIENTコードが小さい順になるように並び替えて出力しました。具体的には、以下のようなイメージで出力します。

//image[images\0801_出力イメージ][成果物イメージ]{
//}

== CSVファイルでデータを出力しよう

全体のコードが長いため、以前と異なる点について細かく解説します。

=== 前回までに取得した項目をまとめる

前章までで取得できた項目を1つのコードにまとめます。

//emlist[][python]{
# 実データを探して取得
for fact in model_xbrl.facts:
    # EDINETコードを探す
    if fact.concept.qname.localName == 'EDINETCodeDEI':
        company_data["EDINETCODE"] = fact.value

    # 企業名を探す
    elif fact.concept.qname.localName == 'FilerNameInJapaneseDEI':
        company_data["企業名"] = fact.value

    # 営業利益(IFRS)を探す
    elif fact.concept.qname.localName == 'OperatingProfitLossIFRS':
        if fact.contextID == 'CurrentYearDuration':
            company_data["営業利益(IFRS)"] = fact.value

    # 事業等のリスクを探す
    elif fact.concept.qname.localName == 'BusinessRisksTextBlock':
        if fact.contextID == 'FilingDateInstant':
            raw_risk = fact.value
            # BeautifulSoupを使ってHTMLタグを除去
            soup = BeautifulSoup(raw_risk, "html.parser")
            company_data["事業等のリスク"] = re.sub(r'\s', '', soup.get_text()).strip()


# 監査データからKAMを探して取得
for fact in model_audit.facts:
    if fact.concept.qname.localName == 'KeyAuditMattersConsolidatedTextBlock':
        if fact.contextID == 'FilingDateInstant':
            raw_kam = fact.value
            # BeautifulSoupを使ってHTMLタグを除去
            soup = BeautifulSoup(raw_kam, "html.parser")
            company_data["KAM"] = re.sub(r'\s', '', soup.get_text()).strip()


# 見つけたデータをリストに入れる
edinet_company_info_list.append(list(company_data.values()))
//}

=== 業種のデータを取得する

次に業種のデータを取得します。有報の中には業種のデータが存在しないため、EDINETが用意したEDINETコードリストを用います。EDINETコードリストの中にはEDINETコードと業種のデータが紐づいています。それを利用して業種データを取得します。

EDIENTのホーム画面より上部のタブから「EDIENTタクソノミ及びコードリスト　ダウンロード」という一番右のタブを開きます。

//image[images\0802_EDINETコードリストを参照_1][EDINETからEDINETコードリストを参照する]{
//}

ページの一番下にある「EDIENTコードリスト」のCSVファイルをダウンロードし、ディレクトリの中に入れます。

//image[images\0803_EDINETコードリストを参照_2][EDINETコードリストをダウンロードする]{
//}

次にEDIENTコードリストを参照できるようにパスを通します。

//emlist[][python]{
def main():
    # EDINETコードリストを追加
    edinetcodedlinfo_filepath = r'C:\Users\ユーザー名\Downloads\Edinetcode_20241007\EdinetcodeDlInfo.csv'
    edinet_info_list = make_edinet_info_list(edinetcodedlinfo_filepath)

    # (ここに有報と監査報告書のXBRLファイルのパスを指定)

    edinet_company_info_list = make_edinet_company_info_list(xbrl_files, edinet_info_list, audit_files)
//}

データを探すコードでEDINETコードを取得する部分に業種を取得するコードを付け足します。

//emlist[][python]{
# EDINETコードを探す
if fact.concept.qname.localName == 'EDINETCodeDEI':
    company_data["EDINETCODE"] = fact.value

    # 業種をEDINETコードに基づいて設定
    for code_name in edinet_info_list:
        if code_name[0] == company_data["EDINETCODE"]:
            company_data["業種"] = code_name[1]
            break
//}

さらにEDINETコードと業種のデータを紐づける関数を作成します。

//emlist[][python]{
def make_edinet_info_list(edinetcodedlinfo_filepath):
        edinet_info = pd.read_csv(edinetcodedlinfo_filepath, skiprows=1, encoding='cp932')
        edinet_info = edinet_info[["ＥＤＩＮＥＴコード", "提出者業種"]]
        edinet_info_list = edinet_info.values.tolist()
        return edinet_info_list
//}

以上で業種のデータを取得出来るようになりました。

=== CSVで出力する

write_csv()関数を作り、CSVファイルで出力します。CSVで出力するためにはPandasというPythonのライブラリを使います。Pandasはデータフレームという二次元表の形にするときに使うライブラリです。インポートのところにPandasを追加します。Pandasはデータフレームというリストをテーブル形式に落とし込むライブラリです。データフレームのカラムに初めに決めた6項目を設定します。

次に今回はEDINETコードが小さい順にソートし、encodingを指定して文字化けを防ぎます。今回はBOM付きのUTF-8である「UTF-8-sig」を指定しました。最後に「xbrl_book.csv」というファイル名で出力します。

//emlist[][python]{
# インポート
import pandas as pd

def write_csv(edinet_company_info_list):
        xbrl_frame = pd.DataFrame(edinet_company_info_list,
                         columns=['EDINETCODE', '企業名', '業種', '営業利益(IFRS)(円)', '事業等のリスク', 'KAM'])

        # EDINETコードでソート
        xbrl_frame_sorted = xbrl_frame.sort_values(by='EDINETCODE', ascending=True)

        # CSVファイルで出力
        xbrl_frame_sorted.to_csv("xbrl_book.csv", encoding='utf-8-sig', index=False)
//}

これでCSVファイルに出力することができます。

=== エラーハンドリングを追加

最後にエラーハンドリングを追加します。エラーハンドリングとは、どこで何のエラーが起きているのかわかるようにしておくことです。エラーハンドリングを追加しておくと、コード自体に問題があるのかデータ自体に問題があるのか、またどういったところを修正すればいいのかなどがわかります。様々な処理をするコードを書く場合はエラーハンドリングを追加することは必須となってきます。

//emlist[][python]{
try:
    (処理)
except Exception as e:
    print(f"処理中にエラーが発生しました:{e}")
//}

これを以下の処理すべてのところに書きます。ソースコードを参考に追記して下さい。

 * EDINETコードと業種を紐づける処理
 * XBRLファイルを読み込む処理
 * 有報を解析する処理
 * 監査報告書を解析する処理
 * CSVを書き込む処理

=== ソースコード

//emlist[][python]{
from arelle import ModelManager
from arelle import Cntlr
import os
import glob
import re
from bs4 import BeautifulSoup
import pandas as pd

def make_edinet_info_list(edinetcodedlinfo_filepath):
    try:
        edinet_info = pd.read_csv(edinetcodedlinfo_filepath, skiprows=1, encoding='cp932')
        edinet_info = edinet_info[["ＥＤＩＮＥＴコード", "提出者業種"]]
        edinet_info_list = edinet_info.values.tolist()
        return edinet_info_list

    except Exception as e:
        print(f"EDINET情報の取得に失敗しました: {e}")
        return []

def make_edinet_company_info_list(xbrl_files, edinet_info_list, audit_files):
    edinet_company_info_list = []
    for index, (xbrl_file, audit_file) in enumerate(zip(xbrl_files, audit_files)):
        company_data = {
            "EDINETCODE": None,
            "企業名": None,
            "業種": None,
            "営業利益(IFRS)": None,
            "事業等のリスク": None,
            "KAM": None,
        }

        try:
            ctrl = Cntlr.Cntlr()
            model_manager = ModelManager.initialize(ctrl)
            model_xbrl = model_manager.load(xbrl_file)
            model_audit = model_manager.load(audit_file)
            print("XBRLファイルを読み込んでいます", ":", index + 1, "/", len(xbrl_files))

        except Exception as e:
            print(f"XBRLファイルの読み込みに失敗しました ({xbrl_file} または {audit_file}): {e}")
            edinet_company_info_list.append(list(company_data.values()))
            continue

        try:
            # 実データを探して取得
            for fact in model_xbrl.facts:
                # EDINETコードを探す
                if fact.concept.qname.localName == 'EDINETCodeDEI':
                    company_data["EDINETCODE"] = fact.value

                    # 業種をEDINETコードに基づいて設定
                    for code_name in edinet_info_list:
                        if code_name[0] == company_data["EDINETCODE"]:
                            company_data["業種"] = code_name[1]
                            break

                # 企業名を探す
                elif fact.concept.qname.localName == 'FilerNameInJapaneseDEI':
                    company_data["企業名"] = fact.value

                # 営業利益(IFRS)を探す
                elif fact.concept.qname.localName == 'OperatingProfitLossIFRS':
                    if fact.contextID == 'CurrentYearDuration':
                        company_data["営業利益(IFRS)"] = fact.value

                # 事業等のリスクを探す
                elif fact.concept.qname.localName == 'BusinessRisksTextBlock':
                    if fact.contextID == 'FilingDateInstant':
                        raw_risk = fact.value
                        # BeautifulSoupを使ってHTMLタグを除去
                        soup = BeautifulSoup(raw_risk, "html.parser")
                        company_data["事業等のリスク"] = re.sub(r'\s', '', soup.get_text()).strip()

        except Exception as e:
            print(f"有報の解析中にエラーが発生しました ({xbrl_file}): {e}")

        try:
            # 監査データからKAMを探して取得
            for fact in model_audit.facts:
                if fact.concept.qname.localName == 'KeyAuditMattersConsolidatedTextBlock':
                    if fact.contextID == 'FilingDateInstant':
                        raw_kam = fact.value
                        # BeautifulSoupを使ってHTMLタグを除去
                        soup = BeautifulSoup(raw_kam, "html.parser")
                        company_data["KAM"] = re.sub(r'\s', '', soup.get_text()).strip()

        except Exception as e:
            print(f"監査報告書の解析中にエラーが発生しました ({audit_file}): {e}")

        # 見つけたデータをリストに入れる
        edinet_company_info_list.append(list(company_data.values()))

    return edinet_company_info_list

def write_csv(edinet_company_info_list):
    try:
        xbrl_frame = pd.DataFrame(edinet_company_info_list,
                         columns=['EDINETCODE', '企業名', '業種', '営業利益(IFRS)(円)', '事業等のリスク', 'KAM'])

        # EDINETコードでソート
        xbrl_frame_sorted = xbrl_frame.sort_values(by='EDINETCODE', ascending=True)

                # CSVファイルで出力する
        xbrl_frame_sorted.to_csv("xbrl_book.csv", encoding='utf-8-sig', index=False)
    except Exception as e:
        print(f"CSVの書き込み中にエラーが発生しました: {e}")

def main():
    # EDINETコードリストを追加
    edinetcodedlinfo_filepath = r'C:\Users\ユーザー名\Downloads\Edinetcode_20241007\EdinetcodeDlInfo.csv'
    edinet_info_list = make_edinet_info_list(edinetcodedlinfo_filepath)

    xbrl_files = glob.glob(r'*xbrl_zip\*\XBRL\PublicDoc\*.xbrl')
    audit_files = glob.glob(r'*xbrl_zip\*\XBRL\AuditDoc\*aai*.xbrl')

    edinet_company_info_list = make_edinet_company_info_list(xbrl_files, edinet_info_list, audit_files)

    write_csv(edinet_company_info_list)
    print("extract finish")

if __name__ == "__main__":
    main()
//}

== まとめ

本章では、XBRLを用いて欲しい情報をCSVファイルで出力することについて解説しました。XBRLを用いることでコピペ間違いなどを防止できます。また、CSVファイルでの出力は見やすいだけでなく、二次利用にも適しています。
