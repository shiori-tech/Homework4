### Homework4　DFS
### ディレクトリ構成

```shell
├──── data
│       ├── graph_small.png
│       ├── links_small.txt
│       ├── links.txt
│       ├── pages_small.txt
│       └── pages.txt
├── .gitignore
├── README.md
├── wikipedia.sample.cc
```
#### C++
```shell
$ g++ -std=c++11 wikipedia_sample.cc && ./a.out
スタートの言葉を入れてください
Google
ゴールの言葉を入れてください
ゲーム
```
　- 実行結果
```shell
Google 457783
ゲーム 92
yes
__________
Google
Android
ゲーム
```
架線の下に経路が出力されます！
時間の都合上、smaii_dataで実行しているので、大きなデータで実行する場合はファイルの読み取りのパス名を書き換えてください。

