# Procesor CSS
<p align="justify">
  Program reads simplified CSS code and processes queries for the program. Accepted commands are:
  <br>
  <br> **** - return to reading CSS
  <br> ? – print number of read CSS blocks;
  <br> i,S,? – print number of selectors in i-th block (blocks are numbered from 1), if the block doesn't exist, skip the query;
  <br> i,A,? - print number of attributes for i-th block, if the block doesn't exist, skip the query;
  <br> i,S,j – print j-th selector for i-th block (blocks and attributes are ordered from 1), if the block or selector doesn't exist, skip the query;
  <br> i,A,n – print the value of the attribute n in the i-tth block, if the attribute or block doesn't exist, skip the query;
  <br> n,A,? – print total (for all blocks) number of occurences of the attribute n (duplicates in one block should be removed at the reading stage). 0 is possible;
  <br> z,S,? – print total (for all blocks) number of occurences of the selector z. 0 is possible;
  <br> z,E,n – print value of attribute n for the selector z, if there is more than one occurence of z selector, the last one is used If z isn't found, skip the query;
  <br> 
  <br> Example imput can look like this:
  <pre>
#breadcrumb 
{
  width: 80%;
  font-size: 9pt;
}
  
  h1, body {
    min-width: 780px;
    margin: 0;
    padding: 0;
    font-family: "Trebuchet MS", "Lucida Grande", Arial;
    font-size: 85%;
    color: #666666;
  }
  
  h1, h2, h3, h4, h5, h6 {color: #0066CB;}
  ????
  ?
  1,S,?
  1,S,1
  1,A,?
  2,A,font-family
  h1,S,?
  color,A,?
  h1,E,color
  1,A,padding
  1,D,*
  ?
  2,D,color
  ?
  
  \****
  h1, h2, h3, h4, h5, h6 {color: #0066FF;}
  ????
  ?
  </pre>
  Results for provided input should look like:
  <pre>
? == 3
1,S,? == 1
1,S,1 == #breadcrumb
1,A,? == 2
2,A,font-family == "Trebuchet MS", "Lucida Grande", Arial
h1,S,? == 2
color,A,? == 2
h1,E,color == #0066CB
1,D,* == deleted
? == 2
2,D, color == deleted
? == 1
? == 2
  </pre>
</p>

## Implementation
<p align="justify">
  Program reads queries and blocks of CSS code. When a new block is read, it is stored in a doubly linked list, where each node can hold multiple blocks. Queries are processed by searching through the list and returning the result. Program doesn't use std::string, as there is custom one implemented.
</p>
