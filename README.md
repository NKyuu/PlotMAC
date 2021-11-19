# EP03 - MAC0216 Técnicas de Programação (2021) </br>
#### Nícolas Marins Pereira | NUSP 11952883

![MAC](https://img.shields.io/badge/MAC-0216-success?style=flat-square) ![C](https://img.shields.io/badge/-C-blue?style=flat-square)
</br></br>
<img src="./resources/usp.png" alt="Logo" style="width: 250px; height: auto;"></br></br>
<!--ts-->
   * [About](#About)
   * [Libraries](#Libs)
   * [How to use](#Tut)
<!--te-->
<p align="left" id="About">
<h2>About</h2></br>
The application is a graph plot software in C. It has both static and dynamic libraries along with the option of utilizing an URL that can be provided instead of a local path/to/file.</br>
</p>
<p align="left" id="Libs">
<h2>Libraries</h2></br>
"local" is a version of the Data.h lib which loads a csv datafile from a local directory while "url", the other version, downloads it from a URL before loading.</br>
Similarly, the "plot" is the version of Graph.h that generates a .png file while "terminal" prints in the bash.</br>
</p>
<p align="left" id="Tut">
<h2>How to use</h2></br>
The main command is: ./[executable] [title] [xlabel] [ylabel] [path]</br>where:</br>
[title] is the title of the plotting,</br>
[xlabel] and [ylabel] are the name of each respective axis,</br>
[path] is or a directory path/to/file or an url https://site.com/path/to/file path.</br> 
</p>