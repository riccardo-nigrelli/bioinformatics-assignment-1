<h1 align='center'>ASSIGNMENT 1</h1>

<p align="center">
  <a href="">
  	<img src="https://img.shields.io/badge/Build-passing-blue.svg" height=25/>
  </a>
  <a href="https://github.com/riccardo-nigrelli/Interpolation/releases">
    <img src="https://img.shields.io/badge/Version-v1.0-e60026.svg" height=25/>
  </a>
</p>

<p>
Through this repository the user can reconstruct the DNA of a gene by starting from a FASTQ file.
The tool fundamentally is a pipeline formed by three steps: 
</p>
<ul>
<li>Reads trimming</li>
<li>Building of the De Bruijn Graph</li>
<li>Recostruction of the DNA via a graph visit</li>
</ul>

<h4> Prerequisites </h4>
<p>To use this tool you need to have <a href="https://graphviz.org/"> graphviz </a> installed.</p>

<h4> Installation </h4>
<ul>
  <li>Download or clone the repository</li>
  <li>Run the <code>dependencies.sh</code> file to complete the initial setup</li>
  <li>Compile and run the tool using the commands in the table below</li>
</ul>

<h4> Usage commands </h4>
<table>
  <tr align="left">
    <th>Command</th>
    <th>Description</th>
  </tr>
  <tr>
    <td><code>make clean all</code></td>
    <td>Generate executable files</td>
  </tr>
  <tr>
    <td><code>./app/main --default</code></td>
    <td>Run application with default setting</td>
  </tr>
  <tr>
    <td><code>./app/main --help</code></td>
    <td>See application usage</td>
  </tr>
</table>
