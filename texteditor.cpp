#include"texteditor.h"
void showInstructions(){
  cout<<"*************Easy TextPad***************\n";
  cout<<"You are not registerd!\n";
  cout<<"Github Opensource Address: https://github.com/orange2008/EasyTextpad\n";
  cout<<"Version: alpha 1.0\n";
  cout<<"Release Date: 2019-05-28-11-52-13\n";
  cout<<"Enter Anything command."<<endl;
  cout<<"0.Help Info"<<endl;
  cout<<"1.View Document Name"<<endl;
  cout<<"2.Change Document Name"<<endl;
  cout<<"3.View Document"<<endl;
  cout<<"4.Move Editor Location"<<endl;
  cout<<"5.Add Text"<<endl;
  cout<<"6.Add Text in Over"<<endl;
  cout<<"7.Count This Document Text Number"<<endl;
  cout<<"8.Find Text(Like Ctrl+F)"<<endl;
  cout<<"9.Delete Text"<<endl;
  cout<<"10.Save file"<<endl;
  cout<<"11.Exit System"<<endl;
  cout<<"******************************************"<<endl;
}
void getChoice(){
    TextEditor editor;
    while(1)
        {
            cout<<"\n";
            cout<<"Please Command(0.View Helps)£º";
            int n;
            cin>>n;
            if(n==11) break;
            switch(n)
            {
                case 0:{
                    showInstructions();
                   break;
                }
                case 1:{
                    cout<<"Document Name is£º"<<editor.getName()<<endl;
                    break;
                }
                case 2:{
                    string s;
                    cout<<"Please type new document name: ";
                    cin>>s;
                    editor.setName(s);
                    cout<<"Successfully!"<<endl;
                    break;
                }
                case 3:{
                    cout<<editor;
                    int line,pos;
                    editor.getCursor(&line,&pos);
                    cout<<"The current number of lines of the cursor is£º"<<line<<" Offset is£º"<<pos<<endl;
                    break;
                }
                case 4:{
                    int line,pos;
                    editor.getCursor(&line,&pos);
                    cout<<"The current number of lines of the cursor is£º"<<line<<" Offset is£º"<<pos<<endl;
                    cout<<"The number of lines the cursor is to move:";
                    cin>>line;
                    cout<<"The position of the cursor on this line:";
                    cin>>pos;
                    editor.setCursor(line,pos);
                    break;
                }
                case 5:{
                    cout<<editor;
                    int line,pos;
                    editor.getCursor(&line,&pos);
                    cout<<"The current number of lines of the cursor is£º"<<line<<" Offset is£º"<<pos<<endl;
                    string text;
                    cout<<"Please enter the text you want to write (in English)£º"<<endl;
                    cin>>editor;
                    break;
                }
                case 6:{
                    cout<<"Please enter the text to add£º"<<endl;
                    string text;
                    char s[100];
                    getchar();
                    gets(s);
                    text = s;
                    editor.addText(text);
                    while(1){
                        cout<<"Continue(Y OR N)£º";
                        string c;
                        cin>>c;
                        if(c[0]!='Y'&&c[0]!='y') break;
                        getchar();
                        gets(s);
                        text = s;
                        editor.addText(text);
                    }
                    break;
                }
                case 7:{
                    int total,space,num,quot,letter;
                    editor.wordState(&total,&letter,&num,&space,&quot);
                    cout<<"The total number of full texts is£º"<<total<<endl;
                    cout<<"The full text letter number is£º"<<letter<<endl;
                    cout<<"The full-text number is£º"<<num<<endl;
                    cout<<"The full-text punctuation number is£º"<<quot<<endl;
                    cout<<"The full text space is£º"<<space<<endl;
                    break;
                }
                case 8:{
                    cout<<"Please enter the text you are looking for:"<<endl;
                    string text;
                    char s[100];
                    getchar();
                    gets(s);
                    text = s;
                    int line=1,offset=-1;
                    editor.findTextInAll(text,&line,&offset);
                    while(1){
                        if(offset==-1) break;
                        cout<<"Text in the "<<line<<"Line number"<<offset<<"Location"<<endl;
                        editor.findTextInAll(text,&line,&offset);
                    }
                    break;
                }
                case 9:{
                    cout<<"1.Delete a piece of text"<<endl;
                    cout<<"2.Delete text at a specific location"<<endl;
                    int as;
                    cout<<"Please enter a selection£º";
                    cin>>as;
                    if(as==1){
                      cout<<"Please enter the text you want to delete:"<<endl;
                      string text;
                      char s[100];
                      getchar();
                      gets(s);
                      text = s;
                      editor.deleteText(text);
                      cout<<"successfully deleted"<<endl;
                    }else if (as ==2){
                       cout<<"Enter the line number£º";
                       int line,pos,length;
                       cin>>line;
                       cout<<"\nInput location£º";
                       cin>>pos;
                       cout<<"\nInput length£º";
                       cin>>length;
                       editor.deleteText(line,pos,length);
                       cout<<"successfully deleted"<<endl;
                    }
 
                   break;
                }
                case 10:{
                editor.saveFile();
                cout<<"Save text successfully£¡"<<endl;
                  break;
                }
                default:
                    cout<<"Input number error"<<endl;
                    continue;
             }
         }
}
int main()
{
    showInstructions();
    getChoice();
    system("echo Do you remember to save your file?If you do not save this file,all the change will lose!");
    system("pause");
    return 0;
}

