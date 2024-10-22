= ライブラリとは何か

本書において、プログラムを用いたコードの実践を行いました。その中で、コードの開始の部分に@<tt>{import re}のような記載がされることがあります。この箇所では、ライブラリのインポートをしています。

ライブラリとは、特定のタスクやプロジェクトに関連する便利な機能をまとめたものです。ライブラリは主に標準ライブラリと外部ライブラリに分類されます。標準ライブラリはPythonで公式に用意されたもので、datetimeモジュールやosモジュールなどです。それに対して、外部ライブラリは別の組織か個人が用意したもので、pandasやnumpyなどです。多くは複数のモジュールがまとめられパッケージで提供されています。

多くは複数のモジュールがまとめられパッケージで提供されています。これらは「import 〇〇」と記述することでコード内で使用することができ、外部ライブラリを使用する際はこの前に「pip install 〇〇」とターミナルにコマンドを入力し、PCにインストールします。ライブラリを使用することで、すでに開発された安全で質の高いプログラムを利用し、より効率的にプログラムが作成出来ます。

//emlist[1][python]{
# モジュールを利用するためのコード
import numpy as np
//}

//emlist[1][python]{
# ライブラリをインストールするためのコード
pip install lightgbm
//}
