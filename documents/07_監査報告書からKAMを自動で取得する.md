# 本章の目的

本稿では今までと少し異なり、有価証券報告書の提出書本書ではなく、監査報告書という書類からデータを取得します。

具体的に取得するデータはKAMという指標です。KAMは「当年度の財務諸表の監査において、監査人が職業的専門家として特に重要であると判断した事項」です。

しかし、KAMは会計士などでない限りあまり知られていないものです。
そのため、監査報告書とKAMがそれぞれどんなものなのかを知り、データを取得できるようなることを目指します。

# 監査報告書とKAMについて

KAMとは「当年度の財務諸表の監査において、監査人が職業的専門家として特に重要であると判断した事項」のことを指し、監査報告書は、このKAMをはじめ、監査人の名前など監査に関わる事項が記載されている書類です。


しかし、監査をする会計士以外の多くの人はあまり監査報告書やKAMというものに関わりがなく、わからない方も多いと思います。この2つについてもう少し詳しく知った上でデータを取得しましょう。

## 監査報告書とは

監査報告書とは日本会計士協会によると「経営者の作成した財務諸表が、一般に公正妥当と認められる企業会計の基準に準拠して、企業の財政状態、経営成績及びキャッシュ・フローの状況をすべての重要な点において適正に表示しているかどうかについて監査人の監査意見を述べた報告書である。」*¹ といった内容の書類です。

簡単にいえば、**「財務諸表の専門家である公認会計士が適正と認めるもの」**です。内容として担当した会計士の名前や監査意見、その根拠などが書いてあります。そのため、世の中に提出されたすべての有価証券報告書に対しこの監査報告書は付随します。

また提出本文書と違う点として、連結と個別で書類が分かれているのも特徴だと思います。

以下がEDIENTで見たときの監査報告書です。いつも開いた後、上部のタブから「監査報告書」を選択するとみることができます。また、監査報告書には連結と個別が別のファイルになっています。上が連結で下が個別です。

![alt text](images\0701_監査報告書の例.png)

## KAMとは

KAM（カム）は「監査上の主要な検討事項」（Key Audit Matters）の略であり、金融庁によると「監査人が実施した監査の透明性を向上させ監査報告書の情報価値を高めることにその意義がある」*² ものとされています。
投資家などからすれば有価証券報告書の本文書と比べると参照されるケースは少ないですが、財務諸表の監査において特に重要なことがKAMに書かれているため、監査報告書の中では重要視されることが多いです。また、企業ごと、事業ごとで業務の体系や詳細は変わってくるでしょう。それらをどう監査のルールに当てはめるのか、その時に懸念しなくてはならなかった点はどういったところなのかなどがKAMには書かれています。そのため中身だけでなく、表の見出しも企業や年度によっても異なります。この見出しだけに注目しても見出しの中にどんな単語が多いのかなど分析ができるほどです。

![alt text](images\0702_KAMの例_1.png)

![alt text](images\0703_KAMの例2.png)

例）トヨタ自動車2023年度のKAM

---

*１　引用：日本公認会計士協会　監査報告書
https://jicpa.or.jp/cpainfo/introduction/keyword/post-77.html

*２　引用：金融庁　「監査上の主要な検討事項（KAM）の特徴的な事例と記載のポイント」の公表
https://www.fsa.go.jp/news/r3/sonota/20220304-2/20220304-2.html


# 監査報告書からKAMを自動で取得しよう

監査報告書とKAMについてどのようなものなのか分かったところで実際にデータを取得してみましょう。

## タクソノミを確認しよう

本章でも有価証券報告書からデータを取得するのと同様に、取得したい情報を示すタクソノミを指定しましょう。

今回は2章で紹介したタクソノミの参照方法の3つ目である、金融庁のタクソノミ要素リストを参照してタクソノミを指定します。理由としてはKAMはどの企業も確実に記載しなくてはならない項目のため標準タクソノミとして準備されています。標準タクソノミは金融庁から提出されているタクソノミ要素リストから確認することができます。こういった標準タクソノミを調べる際は一番見つかりやすい参照方法です。ただし、情報が多すぎてどこを探したらいいのかわからなかったり、たまに間違ったりもするため注意が必要です。

タクソノミ要素リストは以下のURLを踏めば自動でダウンロードができます。

https://www.fsa.go.jp/search/20231211/1e_ElementList.xlsx

1. 目次から「9 企業内容等の開示に関する内閣府令 第三号様式 有価証券報告書(jpcrp03000-asr)」のシートを選択
    
    ![alt text](images\0704_タクソノミ要素リストの目次.png)
    
2. 「Ctrl」＋「F」で検索窓から「監査上の主要な検討事項」と検索
3. 「詳細ツリー‐標準ラベル（日本語）」（B列）でヒットするものを探す
    
    ![alt text](images\0705_タクソノミ要素リスト内で目的の項目を検索.png)
    
4. 「冗長ラベル（日本語）」（C列）で連結のものと個別のものが分かれていることが確認できるため連結のものの「要素名」（I列）を確認
    
    ![alt text](images\0706_タクソノミ要素リストの中から参照する.png)
    

これをkeyとして使用します。

連結と個別それぞれあるため注意してください。
連結のKAMを抽出したいため、タグは**"KeyAuditMattersConsolidatedTextBlock"**となります。

今回は、今までとは異なり、タグが「：」で分かれていないためExcelファイルの I列目である要素名だけ指定しましょう。

context_refに関しては財務情報と異なり、当期のものしかないため**"FilingDateInstant"**で大丈夫です。

以上でタクソノミが準備できました。

## 取得するコードを書こう

大枠は前章までと変わりませんので、異なる点をメインに説明していきます。

まずは、KAMは有価証券報告書の提出本文書ではなく監査報告書にのみ記載されている内容のため、有報のパスだけなく、監査報告書のパスも指定します。

ここで注意点があります。

今まで参照していた有報の中の提出本文書類を示すものが「PublicDoc」です。しかし今回は監査報告書の中からデータを取得したいため、パスを通すときにPublicDocではなく**「AuditDoc」**と指定します。

| EDINETから見たときの名称 | フォルダを開いたときの名称 |
| --- | --- |
| 提出本文書類 | PublicDoc |
| 監査報告書 | AuditDoc |

次にXBRLファイルを選ぶ時なのですが、監査報告書には連結と個別の区別はタクソノミ単位ではなく、ファイル単位で分かれています。今までの正規表現のコードを使用し、PublicDocをAuditDocに変えただけでは欲しいKAMのデータを取るためのファイルが指定できず、データを抜き出すことができなくなってしまいます。

そこで正規表現を使用しても正しくファイルを指定できるようにしていきます。

EDINETからダウンロードした監査報告書のファイル名には略号*³ というものがあり、これを活用していきます。

| 独立監査人の報告書 | 略号 | 基本的な会計のドメイン知識 |
| --- | --- | --- |
| 監査報告書及び内部統制監査報告書 | aai | 連結の情報が載っている |
| 監査報告書 | aar | 個別の情報が載っている |

一般的にこういったものは連結の情報を知りたいことが多いため、連結のデータが存在する**aai**のファイルを指定していきます。

![alt text](images\0707_タクソノミ連結個別の指定.png)

そしてaaiがある場所は AuditDoc と .xbrl の間です。

正規表現を用いてここにaaiが載っているファイルを指定し過不足なくデータを取得できます。

指定ができたらcompany_infoに両方のファイルを忘れずに入れてください。

```python
def main():
    xbrl_files = glob.glob(r'*xbrl_zip\*\XBRL\PublicDoc\*.xbrl')
    audit_files = glob.glob(r'*xbrl_zip\*\XBRL\AuditDoc\*aai*.xbrl')
    
    company_info = make_edinet_company_info_list(xbrl_files, audit_files)
```

次に、ファイルを読み込む部分についてです。こちらでもaudit_filesが読み込まれるようにしましょう。

zipを使用し、有報のデータと監査報告書のデータが一組になるようにします。これでどこかで組み違うことを防止した上で読み込みます。

```python
for index, (xbrl_file, audit_file) in enumerate(zip(xbrl_files, audit_files)):
        company_data = {
            "EDINETCODE": "",
            "企業名": "",
            "KAM": "",
        }
        
        # (コントローラーの設定などは省略)
        
        model_xbrl = model_manager.load(xbrl_file)
        model_audit = model_manager.load(audit_file)
```

EDIENTコードと企業名は有報から取得していますが、KAMは監査報告書から取得するためループ処理も分けて書く必要があります。

またif文の中で先ほど調べたタクソノミを指定します。また、KAMはテキストデータであるためデータを綺麗に整える処理も忘れずに行いましょう。

データをリストに入れる際は最後に入れましょう。最後に入れることで同じリストに入れることができます。逆に言えば、EDIENTコードと企業名を見つけた段階でリストに入れてもらうと別のリストとして保管してしまいます。別のリストで保管すると、企業名とKAMでで俺が対応しているのかわからなくなったり、本来１行に収めたいのにKAMだけ行が分かれてしまったりとごちゃごちゃしてしまう可能性が大いにあります。そのため同じ企業・年度の情報は一つのリストにまとめておきましょう。

```python
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
```

以前より少し長めのコードにはなりますが、同じようなことを2回行っていると思えばそこまで苦ではないでしょう。

以下がすべてをまとめたソースコードになります。

▼ソースコード

```jsx
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
    xbrl_files = glob.glob(r'*xbrl_zip\*\XBRL\PublicDoc\*.xbrl')
    audit_files = glob.glob(r'*xbrl_zip\*\XBRL\\AuditDoc\*aai*.xbrl')
    
    company_info = make_edinet_company_info_list(xbrl_files, audit_files)
    for info in company_info:
        print(info)

    print("extract finish")

if __name__ == "__main__":
    main()
    
```

もし、「XBRLファイルを読み込んでいます：」という文章がなく「extract finish」とだけ表示されて終わってしまう場合はパスが適切に指定できていないため、より詳しいパスを書くなどして適切なパスの指定をしてください。

# まとめ

本章では、監査報告書からKAMという監査をする上で注目した点などのデータを取得しました。普段見ることが多くない書類・項目ではありますが取得が確認できましたね。

次章では今まで取得したデータを一つのコードでまとめてExcel形式で出力するということをします。Excelで出力することによりターミナルで確認するよりも見やすく、二次利用もしやすくなると思います。