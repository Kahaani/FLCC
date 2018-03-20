# FLCC

[![MIT Licence](https://badges.frapsoft.com/os/mit/mit.svg?v=103)](https://opensource.org/licenses/mit-license.php)
[![Build status](https://ci.appveyor.com/api/projects/status/ddbb6dwpxvijgnvh?svg=true)](https://ci.appveyor.com/project/chromezh/flcc)

Fan-chieh Lower Character Connector / 反切下字系聯工具

## 反切系聯法

### 基本條例

切語下字（fan-chieh lower character）與所切之字為疊韻，則切語下字同用者、互用者、遞用者，韻必同類也。同用者，如：東，德紅切，公，古紅切，同用「紅」字也；互用者，如：公，古紅切，紅，户公切，「紅」、「公」二字互用也；遞用者，如：東，德紅切，紅，户公切，「東」字用「紅」字，「紅」字用「公」字也。今據此系聯之，為每韻一類、二類、三類、四類。

### 分析條例

《廣韻》同音之字，不分兩切語，此必陸氏舊例也。其兩切語下字同類者，則上字必不同類。如：紅、戶公切，烘、呼東切，「公」、「東」韻同類，則「戶」、「呼」聲不同類。今分析切語上字不同類者，據此定之也。

上字同類者，下字必不同類。如：公，古紅切，弓，居戎切，「古」、「居」聲同類，則「紅」、「戎」韻不同類。今分析每韻二類、三類、四類者，據此定之也。

### 切下字系聯的補充條例

切語下字既系聯為一類矣，然亦有實同類而不能系聯者，以切語下字兩兩互用故也。如：「朱」、「俱」、「無」、「夫」，四字韻本同類，朱、章俱切，俱、舉朱切，無、武夫切，夫、甫無切，「朱」與「俱」、「無」與「夫」，兩兩互用，遂不能兩類系聯矣。今考平、上、去、入四韻相承者，其每韻分類亦多相承，切語下字既不系聯，而相承之韻又分類，乃據以定其分類。否則雖不系聯，實同類耳。

<p align="right">——《切韻考·條例》</p>

## 等價問題與並查集

### 等價關係

等價關係是現實世界中廣汎存在的一種關係。對於集合 ![](http://latex.codecogs.com/gif.latex?S) 中的關係 ![](http://latex.codecogs.com/gif.latex?R)，若具有自反、對稱和傳遞性，則 ![](http://latex.codecogs.com/gif.latex?R) 是一個等價關係。由等價關係 ![](http://latex.codecogs.com/gif.latex?R) 可以產生集合 ![](http://latex.codecogs.com/gif.latex?S) 的等價類，可以採用並查集高效地求解等價類問題。

### 並查集

並查集支持查找一個元素所屬的集合以及兩個元素各自所屬的集合的合併等運算。當給出兩個元素的一個無序對 ![](http://latex.codecogs.com/gif.latex?(a,b)) 時，需要快速「合併」 ![](http://latex.codecogs.com/gif.latex?a) 和 ![](http://latex.codecogs.com/gif.latex?b) 分別所在的集合，這期間需要反復「查找」某元素所在的集合。「並」、「查」和「集」3 個字由此而來。在這種數據類型中，![](http://latex.codecogs.com/gif.latex?n) 個不同的元素被分爲若干組。每組是一個集合，這種集合叫分離集合，稱之爲並查集（disjoint-set）。

## 使用方法

（以下内容尚待完善）

将 `input.txt` 置于当前目录下。

## 致谢

`input.txt` 提取自 [poem](https://www.zhihu.com/people/poem) 的[广韵字音表(20170209)](https://zhuanlan.zhihu.com/p/20430939)。