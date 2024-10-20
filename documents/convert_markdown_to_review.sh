#!/bin/bash

# 変換するディレクトリを指定
INPUT_DIR="./"
OUTPUT_DIR="./output"

# 出力ディレクトリが存在しない場合は作成
mkdir -p "$OUTPUT_DIR"

# 指定したディレクトリ内のすべての.mdファイルを変換
for markdown_file in "$INPUT_DIR"/*.md; do
  # 拡張子を変更して出力ファイル名を設定
  output_file="$OUTPUT_DIR/$(basename "${markdown_file%.md}.re")"

  # pandoc2reviewを使って変換 (リダイレクトで対応)
  pandoc2review "$markdown_file" > "$output_file"

  echo "変換完了: $markdown_file -> $output_file"

  # hr、sub、embed構文の削除または置き換え
  sed -i -e '/^---$/d' \                                 # '---'行を削除
         -e 's/{sub[^}]*}/(サブスクリプション)/g' \     # 'sub'構文を '(サブスクリプション)' に置き換え
         -e 's/{embed[^}]*}/ありません/g' \             # 'embed'構文を 'ありません' に置き換え
         "$output_file"

done

echo "すべてのファイルの変換と置き換えが完了しました。"
