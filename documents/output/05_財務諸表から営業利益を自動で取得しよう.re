= 財務諸表から営業利益を自動で取得しよう

== 本章の目的

前章までで分析に必要な対象である書類の取得方法を学習しました。本章からは、実際に有報の中からデータを取得をしていきます。今回は、売上高・費用、資産、負債といった財務データをXBRLファイルから取得していきます。財務データを活用することで、投資意思決定に役立つことがありますので、ぜひとも活用してください。

== 1社から取得してみる

財務データを取得する際には、以下に気をつける必要があります。

 * 適用される会計基準は何なのか
 * 連結財務諸表からデータを取得するか、単体財務諸表からデータを取得するか
 * 勘定科目は揃っているか

上記の3項目が統一されていないと、同じコードでデータを取得することは困難になります。それらの対応のためにコードの条件分岐を実施したりするなど、XBRLを利用する際の苦労はこちらに集約されています。

今回はトヨタ自動車株式会社を例に、データの取得を試みようと思います。トヨタ自動車株式会社の分析において、連結財務諸表からデータを抜き出そうと考えた所、適用される会計基準は国際会計基準(IFRS)でした。したがって、国際会計基準(IFRS)を適用している連結財務諸表の営業利益を取得するためのコードを書くことを決めました。

一度に何社も取得するとコードのどの部分でデータを取得しているのかが理解がしづらいため、トヨタ自動車1社から営業利益のデータを抜き出し、データ取得の必要最低限について学んでいきましょう。

== タクソノミを確認しよう

データを取得するにあたってタクソノミを指定します。財務データの取得には「タクソノミのタグ」と「コンテキストIDという期間などを表す指標」の2つ指定が必要です。このタクソノミを参照する方法については主に2章に記載しているため参考にしてください。本章ではそこで紹介した1つ目の「EDINETからCSVファイルをダウンロードして検索」を用いてタクソノミを参照します。EDINETから有報をダウンロードする画面で「CSV」をクリックし、その有報のCSVファイルをダウンロードします。その中の圧縮サイズが一番大きいファイルを開くと以下のような表が出てきます。

//image[0206_タクソノミCSV][csvデータ]{
//}

この表は、その企業で利用されているタクソノミをまとめたもので、標準タクソノミならび提出者タクソノミも掲載されています。特に重要な項目は以下のとおりです。

 * 「要素ID」＝ タグ
 * 「項目名」＝ タグが示す勘定科目や目次など
 * 「コンテキストID」＝ コードのcontext_refに対応するもの、期間や連結・個別を表すもの
 * 「相対年度」＝コンテキストIDに対応する期間
 * 「連結・個別」＝子会社も合わせたグループ会社全体のものかその企業の個別のものか

コード的には要素IDとコンテキストIDがわかればデータの取得が可能となりますが、それだけを見ても内容が人間には判別しづらいため、他の3つのカラムを参照し正しい要素IDとコンテキストIDを見極めます。

では項目名が営業利益である行を探しましょう。項目名を指定して検索をしないと、別の列にはいっている営業利益という単語も拾ってしまうため、ここは留意が必要です。

//image[0501_CSVから営業利益を探す][csvデータ]{
//}

今回の取得条件は「国際会計基準(IFRS)で作成された連結の財務諸表」のため、項目名にも（IFRS）と書かれています。タグの中にはこの会計基準の情報も含まれて細かく区別されています。会計基準が変わると当然比較ができないようにそもそもデータの取得もできないため覚えておきましょう。

以上のようにタクソノミを調べると、要素IDが ”jpigp_cor:OperatingProfitLossIFRS”、コンテキストIDが”CurrentYearDuration”@<fn>{fn1}と特定できました。

ただし、要素IDのみ使用するのは「：」以降の「OperatingProfitLossIFRS」の部分のみとなります。

このタクソノミは次のコーディングの部分で使用するのでメモをしておいてください。

== 取得するコードを書こう

本書では、XBRLを読み取るためにArelleというOSS(オープンソースソフトウェア)を利用します。ArelleはXBRLの中身を検証するためのものです。Pythonのライブラリとしての機能もあり、無料で使用することができるため選びました。

まずXBRLの中身を覗くためにArelleが利用可能な環境にしましょう。ターミナル上で以下を実行し、インストールをしてください。

//emlist{
pip install arelle-release
//}

こちらでArelleが利用可能になります。

続いてコードを細かく分けて解説していきます。

まず有報の中から今回取得する項目を抜き出す準備をしています。今回であれば、営業利益の他に「EDINETCODE」「企業名」を取得し、企業ごとに営業利益が確認できるようにします。

また、取得したデータを入れるための箱を作ります。

//emlist[][python]{
def make_edinet_company_info_list(xbrl_file):
    edinet_company_info_list = []
    company_data = {
        "EDINETCODE": "",
        "企業名": "",
        "営業利益(IFRS)": "",
    }
//}

Arelleを使用するためにコントローラーを初期化し、modelMager.load(xbrl_file)でXBRLデータを読み込みます。

//emlist[][python]{
ctrl = Cntlr.Cntlr()
model_manager = ModelManager.initialize(ctrl)

model_xbrl = model_manager.load(xbrl_file)
//}

具体的な取得したい情報を取得していきます。

for文で読み込んだデータに対し、「.concept.qname.localName =」でタグを指定することによりfactに望んだ実データを入れるようにループ処理をします。

該当したものは「fact.value」で取得できるようになっています。

注意点として、Arelleではタグの指定をするときには先ほど調べたものを丸々コピペするとデータの取得ができません。「：」以降の「OperatingProfitLossIFRS」と指定することでデータの取得が行えます。

また、二重で if文を書き、「contextID = 」でコンテキストIDを指定することにより期間なども指定し情報を一つに絞ることができます。

財務データの多くは当期だけではなく前期なども記載があり任意のデータを絞り込めない、もしくは間違う可能性があるため必ず指定しましょう。

最後に取得したインスタンスを先ほど作成したリストに入れます。

//emlist[][python]{
# 実データを探して取得
for fact in model_xbrl.facts:

        # EDINETコードを探す
        if fact.concept.qname.localName == 'EDINETCodeDEI':
            company_data["EDINETCODE"] = fact.value
            print("EDIENTコード ：", fact.value)

                # 企業名を探す
        elif fact.concept.qname.localName == 'FilerNameInJapaneseDEI':
            company_data["企業名"] = fact.value
            print("企業名 ：", fact.value)

                # 営業利益(IFRS)を探す
        elif fact.concept.qname.localName == 'OperatingProfitLossIFRS': # タグは「：」以降の部分を指定
            if fact.contextID == 'CurrentYearDuration' and company_data["営業利益(IFRS)"] == "":
                company_data["営業利益(IFRS)"] = fact.value
                print("営業利益(IFRS)：", fact.value)

        # 見つけたデータをリストに入れる
    edinet_company_info_list.append([
        company_data["EDINETCODE"],
        company_data["企業名"],
        company_data["営業利益(IFRS)"],

    ])

    return edinet_company_info_list
//}

ここまでの処理を行うXBRLファイルをパスで指定します。

パスとはファイルなどの居場所を示すものであり、VS Codeで目的のファイルを右クリックすることで「パスをコピー」と出てくるためそのままコピペしましょう。（相対パスでも可）また、ターミナル上で結果を確認できるようにprint文を記述します。

//emlist[][python]{
def main():
        # 各人のXBRLファイルのパス(ただコピーしても動きません)
    xbrl_file = r"\xxx\ファイル名\XBRL\PublicDoc\XBRLファイル名.xbrl"

    company_info = make_edinet_company_info_list(xbrl_file)
    for info in company_info:
        print(info)
//}

これらをまとめると以下のようになり、データを取得できるはずです。

//emlist[][python]{
from arelle import ModelManager
from arelle import Cntlr
import os
import glob

def make_edinet_company_info_list(xbrl_file):
    edinet_company_info_list = []
    company_data = {
        "EDINETCODE": "",
        "企業名": "",
        "営業利益(IFRS)": "",
    }

    ctrl = Cntlr.Cntlr()
    model_manager = ModelManager.initialize(ctrl)

    model_xbrl = model_manager.load(xbrl_file)

    # 実データを探して取得
    for fact in model_xbrl.facts:

        # EDINETコードを探す
        if fact.concept.qname.localName == 'EDINETCodeDEI':
            company_data["EDINETCODE"] = fact.value

        # 企業名を探す
        elif fact.concept.qname.localName == 'FilerNameInJapaneseDEI':
            company_data["企業名"] = fact.value

        # 営業利益(IFRS)を探す
        elif fact.concept.qname.localName == 'OperatingProfitLossIFRS': # タグは「：」以降の部分を指定
            if fact.contextID == 'CurrentYearDuration':
                company_data["営業利益(IFRS)"] = fact.value

    # 見つけたデータをリストに入れる
    edinet_company_info_list.append([
        company_data["EDINETCODE"],
        company_data["企業名"],
        company_data["営業利益(IFRS)"],
    ])

    return edinet_company_info_list


def main():
    # 各人のXBRLファイルのパス(ただコピーしても動きません)
    xbrl_file = r"\xxx\フォルダ名\XBRL\PublicDoc\XBRLファイル名.xbrl"

    company_info = make_edinet_company_info_list(xbrl_file)
    for info in company_info:
        print(info)

    print("extract finish")

if __name__ == "__main__":
    main()
//}

これにより、以下のようにトヨタのデータを取得することができました。

//emlist[][python]{

営業利益(IFRS)： 5352934000000
EDIENTコード ： E02144
企業名 ： トヨタ自動車株式会社
['E02144', 'トヨタ自動車株式会社', '5352934000000']
extract finish
//}

== 10社から取得してみる

ここからはより実用的にしていくために今学んだ自動でデータを取得する技術を複数社の書類に対して行います。

今回は、トヨタ自動車株式会社に追加して、国際会計基準(IFRS)で連結財務諸表を使用している、営業利益が記載されている企業が対象になります。

以上の条件に合う企業を10社ピックアップしました。

 * キッコーマン株式会社
 * 東レ株式会社
 * パナソニックホールディングス株式会社
 * トヨタ自動車株式会社
 * 日鉄ソリューションズ株式会社
 * 株式会社ディー・エヌ・エー
 * サッポロホールディングス株式会社
 * ソニーグループ株式会社
 * アサヒグループホールディングス株式会社
 * キリンホールディングス株式会社

EDINETから以上の10社を検索しXBRLのボタンをクリックすることで手動でXBRLファイルをダウンロードすることができます。

先ほどのコードと異なる点は「ファイルパスを1社から10社に増やすこと」と「それぞれの企業に対して自動でデータを取得し、次の企業に移り同じ処理を行うこと」の2つです。

//emlist[][python]{
from arelle import ModelManager
from arelle import Cntlr
import os
import glob

def make_edinet_company_info_list(xbrl_files):
    edinet_company_info_list = []
    for index, xbrl_file in enumerate(xbrl_files):
        company_data = {
            "EDINETCODE": "",
            "企業名": "",
            "営業利益(IFRS)": "",
        }

        ctrl = Cntlr.Cntlr()
        model_manager = ModelManager.initialize(ctrl)

        model_xbrl = model_manager.load(xbrl_file)
        print("XBRLファイルを読み込んでいます", ":", index + 1, "/", len(xbrl_files))

        # 実データを探して取得
        for fact in model_xbrl.facts:

            # EDINETコードを探す
            if fact.concept.qname.localName == 'EDINETCodeDEI':
                company_data["EDINETCODE"] = fact.value

            # 企業名を探す
            elif fact.concept.qname.localName == 'FilerNameInJapaneseDEI':
                company_data["企業名"] = fact.value

            # 営業利益(IFRS)を探す
            elif fact.concept.qname.localName == 'OperatingProfitLossIFRS': # タグは「：」以降の部分を指定
                if fact.contextID == 'CurrentYearDuration':
                    company_data["営業利益(IFRS)"] = fact.value

        # 見つけたデータをリストに入れる
        edinet_company_info_list.append([
            company_data["EDINETCODE"],
            company_data["企業名"],
            company_data["営業利益(IFRS)"],
        ])

    return edinet_company_info_list

def main():
        # 各人のXBRLファイルのパス(ただコピーしても動きません)
    xbrl_files = glob.glob(r'*フォルダ名\*\XBRL\PublicDoc\*.xbrl')


    company_info = make_edinet_company_info_list(xbrl_files)
    for info in company_info:
        print(info)

    print("extract finish")

if __name__ == "__main__":
    main()
//}

▼結果

//emlist{
XBRLファイルを読み込んでいます : 1 / 10
XBRLファイルを読み込んでいます : 2 / 10
XBRLファイルを読み込んでいます : 3 / 10
XBRLファイルを読み込んでいます : 4 / 10
XBRLファイルを読み込んでいます : 5 / 10
XBRLファイルを読み込んでいます : 6 / 10
XBRLファイルを読み込んでいます : 7 / 10
XBRLファイルを読み込んでいます : 8 / 10
XBRLファイルを読み込んでいます : 9 / 10
XBRLファイルを読み込んでいます : 10 / 10
['E00435', 'キッコーマン株式会社', '66733000000']
['E00873', '東レ株式会社', '57651000000']
['E01772', 'パナソニックホールディングス株式会社', '360962000000']
['E02144', 'トヨタ自動車株式会社', '5352934000000']
['E05304', '日鉄ソリューションズ株式会社', '35001000000']
['E05460', '株式会社ディー・エヌ・エー', '-28270000000']
['E00393', 'サッポロホールディングス株式会社', '11820000000']
['E01777', 'ソニーグループ株式会社', '1208831000000']
['E00394', 'アサヒグループホールディングス株式会社', '244999000000']
['E00395', 'キリンホールディングス株式会社', '150294000000']
extract finish
//}

基本的には先ほどと同じことをしておりますので、ここではコードを変えた箇所について確認していきましょう。

対象企業が増えたため同じ処理をすべてのXBRLファイルで行うためにfor文でループ処理を行います。

また、長時間になる場合もありますのでprint文で全体で何社分行うのか、現在どのあたりの処理をしているのかというのが確認できるようにしてあります。

//emlist[][python]{
for index, xbrl_file in enumerate(xbrl_files):
        　　　　　・
        　　　 （省略）
       　　　　　 ・
        print("XBRLファイルを読み込んでいます", ":", index + 1, "/", len(xbrl_files))
//}

main()関数のところでは、先ほど同様に対象のXBRLファイルのパスを指定する必要があります。1社ずつパスを書いても正常に動くのですが、対象のファイルが増えるほど面倒であるため、正規表現を使用しています。

正規表現とは、直接パスを通したものだけに処理をするのではなく「パターンに一致するものすべて」に処理をするためのものです。globモジュールはそういった時に使用され、「ｒ」の中のクオーテーションの中がそのパターンの型になっています。また「＊」はどんな文でも、何文字でも入れることができるという意味を持ちます。そのため、ここが固有値に当たる部分を指定するとうまくいきます。

パスはそのファイルの居場所であるため環境により異なります。そのため、同じ通りにコード書いてもパスが異なっているとうまく動作しません。対象ファイルが過不足なく指定できるように気を付けて書くようにしてください。

//emlist[][python]{
xbrl_files = glob.glob(r'*フォルダ名\*\XBRL\PublicDoc\*.xbrl')
//}

== まとめ

この章では、XBRLを使用して有価証券報告書から、企業のEDINETコードと企業名、そして財務情報である営業利益を取得しました。財務データを取得できるようになると、同じ業種などで企業を比較などがしやすくなります。財務データはXBRLファイルを直接見てもタグが見つけられないことが少しネックですが、正しく指定してあげればかなり有効に使えるでしょう。その一方で、会計基準の違いなどによりタグが異なると一気に取得することもできないため、そのような会計のドメイン知識も必要になってきます。また、XBRLのタグは正しく付与されていないことも時々あり、そのせいでデータが上手く取得できないと嘆く人も多いです。多くのXBRLユーザーがXBRLに苦労するところがタグなのです。このタグの操作は実際にやってみないとわからない点が多いので、苦しみながら学習していきましょう。

次章では非財務情報であるテキストデータを取得していきます。

//footnote[fn1][期間を表すコンテキストIDが何を指すのかについては表の右隣の相対年度の列を参照してください。要素名、項目名が全く同じであってもこのコンテキストIDが違うと年度が違うということです。多くの場合、最新の情報を求めるため、「当期」を取得することが多いと思います。また、連結・個別の区別もコンテキストIDで区別することがあるので注意して下さい。]
