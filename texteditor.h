#ifndef TEXTEDITOR_H_INCLUDED
#define TEXTEDITOR_H_INCLUDED
#include"string.h"
#include<iostream>
#include<list>
#include<fstream>
#include<algorithm>
using namespace std;
class TextEditor{
private:
     int cursor;
     int line;
     int offset;
     int total;
     int letters;
     int quots;
     int nums;
     int spaces;
     string textName;
     list<string> article;
public:
    TextEditor();
    ~TextEditor();
    const string  & getName() const;
    void setName(const string &name);
    int  getCursor(int *,int *) const;
    int moveCursor(int);
    int setCursor(int ,int);
    int addText(const string &);
    int insertText(string);
    int findTextInAll(const string &,int *,int *);
    int deleteText(const string &);
    int deleteText(int ,int,int);
    int saveFile();
    void wordState(int *,int *,int *,int *,int *) const;
    list<string>::iterator getIndex(int x);
    friend ostream & operator<<(ostream &,TextEditor &);
    friend istream & operator>>(istream &,TextEditor &);
};
  TextEditor:: TextEditor(){
             textName = "Untitled";
             cursor=1;
             line=1;
             offset=0;
             total =0;
             spaces =0;
             quots =0;
             letters = 0;
             nums = 0;
  }
  TextEditor::~TextEditor(){
 
  }
list<string>::iterator TextEditor::getIndex(int x){
      if(x<0)x=0;
      if(x>line)x=line;
      list<string>::iterator it;
      int l = 0;
      for(it=article.begin();it!=article.end();it++){
        l++;
        if(l==x) break;
      }
      return  it;
  }
const string & TextEditor::getName() const{
     return textName;
}
void TextEditor::setName(const string &name){
    if(name.length()!=0){
        textName=name;
    }
}
int  TextEditor::getCursor(int * pLine=NULL,int *pOffset=NULL) const{
          *pLine = cursor;
           *pOffset=offset;
           return 1;
}
int TextEditor::moveCursor(int offset){
         list<string>::iterator it =getIndex(cursor);
         this->offset+=offset;
         while(it->length()<this->offset&&it!=article.end()){
            this->offset-=it->length();
            cursor++;
            it++;
         }
         return 1;
}
int TextEditor::setCursor(int line ,int offset){
          if(line>article.size()) line = article.size();
          this->cursor=line;
          if(offset<0) offset=0;
          if(offset>getIndex(line)->length()) offset = getIndex(line)->length();
          this->offset=offset;
          return 1;
}
int TextEditor::addText(const string & text){
     article.push_back(text);
     total+=text.length();
     for(int i=0;i<text.length();i++){
        if(text[i]==' ') spaces++;else
        if(text[i]>='0'&&text[i]<='9') nums++;else
        if(text[i]>='a'&&text[i]<='z') letters++;else
        if(text[i]>='A'&&text[i]<='Z') letters++;else
        quots++;
     }
     line++;
     return 1;
}
int min(int x,int y)
{
    return x<y?x:y;
}
int TextEditor::insertText(string text){
     total+=text.length();
     for(int i=0;i<text.length();i++){
        if(text[i]==' ') spaces++;else
        if(text[i]>='0'&&text[i]<='9') nums++;else
        if(text[i]>='a'&&text[i]<='z') letters++;else
        if(text[i]>='A'&&text[i]<='Z') letters++;else
        quots++;
     }
     if(article.empty()) {
        article.push_back(text);
        offset = text.length();
        return 1;
     }
     list<string>::iterator it = getIndex(cursor);
 
     string temp=it->substr(0,offset);
     temp+=text;
     temp +=it->substr(offset);
     *it = temp;
     return 1;
}
int TextEditor::findTextInAll(const string & text ,int *line,int *offset){
       list<string>::iterator it;
       int l=0;
       int li = *line;
       int pp = *offset;
       for(it=article.begin();it!=article.end();it++){
            l++;
         if(*line>l) continue;
         if(*line<l) *offset = -1;
         if(it->find(text,(*offset)+1)!=string::npos){
            *line = l;
            *offset = it->find(text,(*offset)+1);
            return 1;
         }
       }
       if(li==*line&&pp==*offset) *offset=-1;
       return 1;
}
 
int TextEditor::deleteText(const string & text){
      int line=1,offset=-1;
      findTextInAll(text,&line,&offset);
      while(1){
        if(offset==-1)break;
        cout<<"Are you sure to delete"<<line<<"location"<<offset<<"DATA(Y of N):";
        char c[100];
        cin>>c;
        if(c[0]!='Y'&&c[0]!='y') continue;
        deleteText(line,offset,text.length());
        findTextInAll(text,&line,&offset);
      }
}
int TextEditor::deleteText(int cursor ,int pos,int length){
         list<string>::iterator it = getIndex(cursor);
         total-=length;
         string text = *it;
         for(int i=pos;i<min(it->length(),pos+length);i++){
            if(text[i]==' ') spaces--;else
            if(text[i]>='0'&&text[i]<='9') nums--;else
            if(text[i]>='a'&&text[i]<='z') letters--;else
            if(text[i]>='A'&&text[i]<='Z') letters--;else
               quots--;
         }
         *it = it->erase(pos,length);
}
void TextEditor::wordState(int *pTotal,int *pLetter,int *pDigit,int *pSpace,int *pQuot) const{
    *pTotal = total;
    *pLetter =letters;
    *pDigit = nums;
    *pSpace =spaces;
    *pQuot = quots;
}
ostream & operator<<(ostream & out,TextEditor & editor){
      int line = 1;
      list<string>::iterator it;
      out<<"***********"<<editor.textName<<".txt*********"<<endl;
      for (it = editor.article.begin();it!=editor.article.end();it++){
        out<<line++<<":";
        out<<*it<<endl;
      }
      out<<endl;
      return out;
}
istream & operator>>(istream & in,TextEditor &editor){
    char s[100];
    getchar();
    gets(s);
    string text(s);
    editor.insertText(text);
    while(1){
        cout<<"Continue(Y OR N)£º";
        string c;
        in>>c;
        if(c[0]!='Y'&&c[0]!='y') break;
        getchar();
        gets(s);
        string ss(s);
        editor.insertText(ss);
    }
    return in;
}
int TextEditor::saveFile(){
    string name = textName+".txt";
    ofstream out(name.c_str(),ios::out);
    list<string>::iterator it;
    for(it=article.begin();it!=article.end();it++){
        out<<*it<<endl;
    }
    out.close();
}
#endif // TEXTEDITOR_H_INCLUDED

