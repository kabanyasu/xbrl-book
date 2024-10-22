= はじめに

まずは本書を手にとっていただき、誠にありがとうございます。本書は「初心者のためのXBRL」をテーマに、XBRLの基礎的な知識から実際にデータを取得する方法を解説します。また、XBRLから取得したテキストを用いた簡単な分析の例も紹介しております。

== 本書の特徴

本書は、XBRL（eXtensible Business Reporting Launguage）という、財務報告をするための国際規格であるコンピュータ言語の取り扱いについて紹介していきます。本書では、主に有価証券報告書という上場企業の決算書等が掲載された書類をXBRLで取得、Pythonを用いて分析を行います。また、本書はXBRLを知らない方であってもXBRLがどういった技術で、どのようにしたらデータを取得できるのかということを中心に解説しております。そのため、初心者に理解しづらいXBRLの仕様などについては適宜省略しております。

また、プログラミング学習において共通事項にはなりますが、なるべく手を動かしてコードを書いてみましょう。手を動かすｒと格段に学習効果が上がります。

また、本書のサンプルコードは以下リンクに記載しておりますので、適宜参考にしながら学習してください。

https://github.com/black76-yy/xbrl_analyze_ontology.git

== 対象読者

本書の対象読者は、以下のような方を想定しております。

 * XBRLについて今は全く知らないけれど、財務情報を用いた分析を行いたい方
 * 有価証券報告書等のデータを用いて株式投資に役立てたい方
 * XBRLの活用例を知りたい経理人材や公認会計士
 * 財務情報を用いたテキスト解析を行いたい研究者やエンジニア
 * テキスト分析を行うための元ネタを拾いたいエンジニアの方

本書を読み進めるための基礎知識については随所で触れるようにしておりますが、Pythonなどの基礎知識を持ったうえで学習しておく方がスムーズにコードを動かしやすいかと思います。

== 参考

本書の参考文献は以下になります。詳しすぎて解説を省略しているものについては、適宜以下のリンク先などを参考にしながら読み進めて頂けると幸いです。

 * @<href>{https://www.xbrl.or.jp/modules/pico1/index.php?content_id=9,一般社団法人 XBRL JAPAN 「XBRLとは」}
 * @<href>{https://www.jpx.co.jp/equities/listing/disclosure/xbrl/02.html,日本取引所グループ　「適時開示情報のXBRL化」}
 * @<href>{https://www.fsa.go.jp/search/20231211.html,金融庁　「2024年版EDINETタクソノミの公表について」}
 * @<href>{https://www.xbrl.or.jp/modules/pico1/index.php?content_id=9,一般社団法人 XBRL Japan - XBRL Japan Inc. - XBRLとは}
 * @<href>{https://www8.cao.go.jp/shougai/suishin/tyosa/r02kokusai/h2_02_01.html#:~:text=ＥＳＧとは、Environment（環境,経営・事業活動を指す。,2.2.1 ＥＳＧとは何か｜令和２年度障害者差別の解消の推進に関する国内外の取組状況調査報告書 - 内閣府}
 * @<href>{https://disclosure2dl.edinet-fsa.go.jp/guide/static/disclosure/WZEK0110.html,EDINET操作ガイド　EDINET API仕様書(Version2)}
 * @<href>{https://www.jstage.jst.go.jp/article/jarms/53/0/53_112/_article/-char/ja/,「Covid-19パンデミックに関する有価証券報告書「事業等のリスク」の記載の変化」渡部 美紀子、　2022年『危険と管理』53巻：p.112-128日本リスクマネジメント学会発行 2024年10月15日}
 * @<href>{https://qiita.com/XBRLJapan/items/27e623b8ca871740f352,Qiita　XBRL Japan「EDINET APIを利用して、企業情報（XBRLデータ）を自動で集めてみよう(4/10)」}
 * @<href>{https://qiita.com/XBRLJapan/items/b1e66f79d597df7b6037#122-xbrlparser%E3%81%AE%E3%82%A4%E3%83%B3%E3%82%B9%E3%83%88%E3%83%BC%E3%83%AB,Qiita　XBRLJapan「EDINET開示のXBRLデータ空、平均給与等の従業員情報を自動で抽出してみよう(5/10)」}
 * @<href>{https://jicpa.or.jp/cpainfo/introduction/keyword/post-77.html,日本公認会計士協会　監査報告書}
 * @<href>{https://www.fsa.go.jp/news/r3/sonota/20220304-2/20220304-2.html,金融庁　「監査上の主要な検討事項（KAM）の特徴的な事例と記載のポイント」の公表}
 * @<href>{https://www.pwc.com/jp/ja/knowledge/prmagazine/pwcs-view/202101/key-audit-matters-diclosure.html,PwC 「KAMの開示に向けてーKAMの基本事項と留意点」}

== 免責事項

本書に記載された内容は、情報の提供のみを目的としています。したがって、本書を用いた開発、制作、運用は、必ずご自身の責任と判断によって行ってください。これらの情報による開発、制作、運用の結果については、著者はいかなる責任も負いません。

== 表記関係について

本書に記載されている会社名、製品名などは、一般に各社の登録商標または商標、商品名です。会社名、製品名については、本文中では©、Ⓡ、™マークなどは表示していません。
