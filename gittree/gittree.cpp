/***************************************************************************
Vse prava zashisheni :) avtor DEmoN  e-mail: tiger_85@bk.ru 

Nagljadnoe predstavlenie osnovnih operacii nad dvoichnimi derevjami,
ispol'zovalas' graficheskaja biblioteka egavga.bgi

Realisovano derevo poiska!!

Ypravlenie: '+3'  dobavit'element v derevo s vesom 3
            '-3'  ydaljaem is dereva element c vesom 3

****************************************************************************
*/


#include <stdlib.h>
#include <stdio.h>
#include <graphics.h>
#include <conio.h>    // getch
#include <ctype.h>

struct tree {
      char info;            //pole dannih
      struct tree *left;    //ykazatel' na levoe podderevo
      struct tree *right;   //ykazatel' na pravoe podderevo
};

struct tree *root; // ykazatel' na koren' vsego dereva

struct tree *stree (struct tree *root, // ykazatel' na koren' vsego dereva
            struct tree *r,    // ykazatel' na koren' novogo poddereva
            char info)         // pole dannih
{
   if (!r){
      r = (struct tree *) malloc(sizeof(struct tree));
      if (!r){
       printf("Error in memory (1)\n");
       exit(0);
     }
     r->left = NULL;
     r->right = NULL;
     r->info = info;
     if (!root) return r;
     if (info<root->info) root->left = r;
     else root->right = r;
     return r;
   }

  if (info < r->info)
    stree(r, r->left, info);
  else
    stree(r, r->right, info);

   return root;
  }

void  print_tree2(struct tree *r,
          int x1,          // levaja gran X
          int x2,          // pravaja gran X
          int y0 )       // coord y
{
  int x0, wrkx1, wrkx2, wrky;
  char buf[20];
  int oldcolor;
  int dy;
  dy = 50;

  if (!r) return;

  x0 = (x1+x2)/2;
  wrky = y0+dy;

  if(r->left != NULL){
    wrkx1=x1;
    wrkx2=x0;
    line(x0,y0,(wrkx1+wrkx2)/2,wrky);
    print_tree2(r->left,wrkx1,wrkx2,wrky);
  }
  if(r->right != NULL){
    wrkx1=x0;
    wrkx2=x2;
    line(x0,y0,(wrkx1+wrkx2)/2,wrky);
    print_tree2(r->right,wrkx1,wrkx2,wrky);
  }
  //narisovat' uzel
  oldcolor=getcolor();
  setcolor(6);
  circle(x0,y0,10);
  setcolor(oldcolor);

  //nadpisat' uzel
  sprintf(buf,"%d",r->info);
  settextjustify(CENTER_TEXT, CENTER_TEXT);
  outtextxy(x0,y0,buf);
}
/**
realizaciya funkcii poiska
*/
/* realizaciya funkcii poiska */
 struct tree *search_tree(struct tree *root, char key){
    if(!root) return root; //pustoe derevo

    while(root->info !=key){
       if (key<root->info)  root=root->left;
       else root=root->right;
       if(root==NULL) break;
    }
    return root;
 }

struct tree *dtree(struct tree *root, char key){

    struct tree *p, *p2;

    if(!root) return root; //vershina ne naidena

    if(root->info==key){  //ydaleniye kornya
    //pystoe derevo
       if(root->left == root->right){
      free(root);
      return NULL;
       }else
       if(root->left == NULL){  //esli odno iz podderev'ev pusto
       p = root->right;
       free(root);
       return p;
       }else
       if(root->right == NULL){
       p = root->left;
       free(root);
       return p;
       }else{
      // est' oba poddereva
    p2 = root->right;
    p = root->right;
     while(p->left)  p=p->left;
     p->left = root->left;
     free(root);
     return p2;
       }
   }

      if(root->info < key) root->right = dtree(root->right,key);
      else root->left = dtree(root->left,key);
      return root;

}

int main (void){

   int i;
   int ch;
   int num,num2;
   char buf[20];
   int gdriver = DETECT, gmode, errorcode;

     char s[] = {32,
        16,48,
        8,24,40,56,
        4,12,20,28,36,44,52,60,
        2,6,10,14,18,22,26,30,34,38,42,46,50,54,58,62};
	 /**
initialize graphics and local variables
*/
    // initialize graphics and local variables
    initgraph(&gdriver, &gmode, "");

    // read result of initialization
    errorcode = graphresult();
    if (errorcode != grOk)  // an error occurred
    {
       printf("Graphics error: %s\n", grapherrormsg(errorcode));
       printf("Press any key to halt:");
       getch();
       exit(1); // terminate with an error code
    }

      root = NULL; //nachal'naya inicializaciya dereva

      //sozdaniye binarnogo  dereva is massiva s[]
      for(i=0;i<sizeof(s)/sizeof(*s);i++)  root = stree(root, root, s[i]);
      // sizeof(s)/sizeof(*s) - kol-vo elementov
	  /**
pechat' ishodnogo massiva v  vide  binarnogo  dereva
*/
      //pechat' ishodnogo massiva v  vide  binarnogo  dereva (vizualiz.)
      print_tree2(root, 1, getmaxx(), 40);

       settextjustify(LEFT_TEXT, TOP_TEXT);
       outtextxy(100,350,"Vvedte operaciju(+-) i nomer. ESC-vyhod.");

    for(;;){
    ch = getch();
    if(ch==27) break;    //ESC

    if(ch=='+'){
        buf[0]='+';
        num=0;
        i=1;
        settextjustify(LEFT_TEXT, TOP_TEXT);

        for(;;){
              buf[i]='\0';
              outtextxy(200,400,buf);
              ch = getch();
              if(isdigit(ch)){
             num2 = num*10+ch-'0';
             if(num2>0 && num2<64){
             num=num2;
             buf[i++]=ch;
        }

      }else if(ch==27){    //ESC
          cleardevice();
          print_tree2(root, 1, getmaxx(), 40);
          settextjustify(LEFT_TEXT, TOP_TEXT);
          outtextxy(100,350,"Vvedte operaciju(+-) i nomer. ESC-vyhod.");
          break;
      }else if(i!=1 && ch=='\r'){
		  /**
Check
*/
        //proverit' otsutstvie i dobavit' v derevo
         if(search_tree(root, num)==NULL){
        root = stree(root, root, num);
        cleardevice();
        print_tree2(root, 1, getmaxx(), 40);
        settextjustify(LEFT_TEXT, TOP_TEXT);
        outtextxy(100,350,"Vvedte operaciju(+-) i nomer. ESC-vyhod.");
        break;
         }else{
        cleardevice();
        print_tree2(root, 1, getmaxx(), 40);
        settextjustify(LEFT_TEXT, TOP_TEXT);
        outtextxy(100,350,"Vvedte operaciju(+-) i nomer. ESC-vyhod.");
        break;
         }
      }
    }
      }
      if(ch=='-'){
    buf[0]='-';
    num=0;
    i=1;
    settextjustify(LEFT_TEXT, TOP_TEXT);
    for(;;){
      buf[i]='\0';
      outtextxy(200,400,buf);
      ch = getch();
      if(isdigit(ch)){
        num2 = num*10+ch-'0';
        if(num2>0 && num2<64){
          num=num2;
          buf[i++]=ch;
        }
      }else if(ch==27){    //ESC
        cleardevice();
        print_tree2(root, 1, getmaxx(), 40);
        settextjustify(LEFT_TEXT, TOP_TEXT);
        outtextxy(100,350,"Vvedte operaciju(+-) i nomer. ESC-vyhod.");
        break;
      }else
      if(i!=1 && ch=='\r'){
         if(search_tree(root, num)!=NULL){
        root = dtree(root, num);
        cleardevice();
        print_tree2(root, 1, getmaxx(), 40);

        settextjustify(LEFT_TEXT, TOP_TEXT);
        outtextxy(100,350,"Vvedte operaciju(+-) i nomer. ESC-vyhod.");
        break;
         }else{
        cleardevice();
        print_tree2(root, 1, getmaxx(), 40);
        settextjustify(LEFT_TEXT, TOP_TEXT);
        outtextxy(100,350,"Vvedte operaciju(+-) i nomer. ESC-vyhod.");
        break;
         }
      }
    }
      }
    }
   closegraph();
   return 0;
}