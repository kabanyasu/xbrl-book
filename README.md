# xbrl-book

## 締め切り

- 2024/10/15までに形をつくりましょう

## 作業のルール

1. まずはブランチを切る
2. 切ったブランチ上で作業を行う
3. マージする時は稲垣にプルリクエストをする
4. 稲垣レビューが完了したらマージを行う
5. 1に戻って繰り返しを行う

## ドキュメントの作成方針

- 基本的にMarkdownで作成をすること
- Markdown作成時に、オートフォーマッターを使う時は以下に気をつける
  - 英字とか数字を入れる時に空白が自動で入らないようにする

## 目次案

いかに追記する。
# はじめに
## 本書の特徴
## ペルソナ
## サンプルコード


# 1章：XBRLの基礎知識
## 本章の目的
## XBRLとは
## XBRLの特徴
## XBRLのメリット
## XBRLの問題点
## まとめ

# 2章：タクソノミと有報
## 本章の目的
## タクソノミとインスタンス
## 有価証券報告書とは
## データを取得するために
## タクソノミの参照方法
### CSVファイルをダウンロードして検索
### XBRLファイル内で検索
### 金融庁のタクソノミ要素リストを参照する
## まとめ

# 3章：たくさんの有報を自動でダウンロードしよう
## 本章の目的
## 事前準備
### EDINET APIを使えるようにしよう
#### 注意点
#### アカウント作成
### コードエディタを使おう
#### VS Codeを使えるようにしよう
## たくさんの有報のデータを自動でダウンロードしよう
## コラム：フィルタリングしてダウンロードの出来る出来ない
## 応用：フォルダ名を企業名にしてダウンロードしてみよう
## まとめ

# 4章：財務諸表から営業利益を自動で取得しよう
## 本章の目的
## 1社から取得してみる
### タクソノミを確認しよう
### 取得するコードを書こう
## 10社から取得してみる
## まとめ

# 5章：有報からテキストデータを自動で取得しよう
## 本章の目的
## 有報から事業等のリスクだけを自動で取得しよう
### タクソノミを確認しよう
### 取得するコードを書こう
## まとめ

# 6章：監査報告書からKAMを自動で取得しよう
## 本章の目的
## 監査報告書とKAMについて
### 監査報告書とは
### KAMとは
## 監査報告書からKAMを自動で取得しよう
### タクソノミを確認しよう
### 取得するコードを書こう
## まとめ

# あとがき
