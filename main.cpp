#include <bits/stdc++.h>
using namespace std;
//1111111
            int DECK_SIZE=52; //卡片最多52張
            const int MAX_HAND_SIZE=10;

            //產生新的撲克牌
            void generateDECK(pair<string, string> deck[])
            {
                string suits[]={"S", "H", "D", "C"};//產生新的花色(好像沒辦法顯示)
                string ranks[]={"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};//產生各種數字
                //接下來用產生各種花色跟數字的組合，並把它儲存在deck這個array裡面
                int index=0;
                for(const string& suit:suits)
                {
                    for(const string& rank:ranks)
                    {
                        deck[index++] = make_pair(suit, rank);
                    }
                }
            }

            //隨機洗牌
            /*
                這邊講解一下，rand這著函數如果是rand()%5會產生0-4
                但我這邊DECK的大小還是用52是因為我的撲克牌排序編號是從0-51
                還有另一個隨機撲克牌的方法是看位置有沒有牌，有就重牌，但時間有點久QQ
                deck[52]={0};
                for(int i=0;i<52;i++)
                {
                    int j=rand()%52;
                    while(deck[j]!=0)
                    {
                        j=rand()%52;
                    }
                    deck[j]=i;
                }

            */
            void randomDECK(pair<string, string> deck[])
            {
                for(int i=0;i<DECK_SIZE;i++)
                {
                    int j=rand()%DECK_SIZE;
                    swap(deck[i],deck[j]);//把原本排好的交換
                }
            }

            //計算手上的牌的總點數
            int countPOINT(const pair<string, string> hand[], int size)
            {
                int points=0;
                int anum=0;
                for(int i=0;i<size;i++)
                {
                    char rank=hand[i].second[0]; //把手上的牌開始分類然後計算點數
                    if(rank=='A') //如果是A就先加11點
                    {
                        points+=11;
                        anum++; //這邊先算有幾張A等等就知道為什麼了:)
                    }
                    else if(rank=='1'||rank=='Q'||rank=='J'||rank=='K')
                    {
                        points+=10; //如果是KQJ就加10點，rank=='1'是指10
                    }
                    else
                    {
                        points+=rank-'0'; //其他都是一般數字直接加，不過因為字元所以要先-'0'換成相對應的數字，像'0'=48、'5'=53，那這樣相減就會是53-48=5
                    }
                    //cout<<"point "<<points<<endl;
                }
                //當點數大於21時且有拿到A
                while(points>21&&anum>0)
                {
                    points-=10; //先讓points減10因為A可以是1或是11
                    anum--; //減完10點後就少一個減10點的機會
                }
                return points; //回傳點數
            }

            //印出撲克牌，對...就印出來XD
            void printHECK(const pair<string, string> hand[],int size)
            {
                for(int i=0;i<size;i++)
                {
                    cout<<hand[i].first<<hand[i].second<<" ";
                }
                cout<<endl;
            }

//3333333333
string decrypt(const string& message, int offset)
{
    string decryptmessage=""; //還沒解密前設為空字串，用於存儲解密後的訊息
    for(char c:message)
    {
        if(isalpha(c)) //判斷是不是字母的函式
        {
            char base=isupper(c)? 'A':'a'; //確定字母的大小寫，base確定了字元在字母表中的基準位置
            char decryptalpha=(c-base-offset+26)%26+base;
            //解密，先將字元c減去基準值base,再減去偏移量offset，因為可能有負值產生，所以加26取餘數，最後把base加回去看大小寫
            decryptmessage+=decryptalpha; //將解密後的字元加入到解密訊息中
        }
        else
        {
            decryptmessage+=c; //不是字母的符號保持原樣
        }
    }
    return decryptmessage; //回傳解密後的訊息
}

//4444444444444444

const int WIDTH=10;
const int HEIGHT=30;
char board[WIDTH][HEIGHT];
void blankboard()
{
    for(int i=0;i<WIDTH;i++)
    {
        for(int j=0;j<HEIGHT;j++)
        {
            board[i][j]=' ';
        }
    }
}
void renderboard()
{
    for(int k=0;k<HEIGHT;k++)
    {
        cout<<"-";
    }
    for(int i=0;i<WIDTH;i++)
    {
        for(int j=0;j<HEIGHT;j++)
        {
            cout<<board[i][j];
        }
        cout<<endl;
    }
    for(int k=0;k<HEIGHT;k++)
    {
        cout<<"-";
    }
    cout<<endl;
}
void Line(int x1,int y1,int x2,int y2)
{
    if(x2>x1) swap(x1,x2);
    if(y2>y1) swap(x1,x2);
    for(int i=x1;i<=x2;i++)
    {
        for(int j=y1;j<=y2;j++)
        {
            board[i][j]='*';
        }
    }
}
void Rectangle(int x1,int y1,int x2,int y2)
{
    for(int i=x1;i<=x2;i++)
    {
        board[i][y1]='*';
        board[i][y2]='*';
    }
    for(int j=y1;j<=y2;j++)
    {
        board[x1][j]='*';
        board[x2][j]='*';
    }
}
void Circle(int centerX,int centerY,int radius)
{
    for(int i=0;i<WIDTH;i++)
    {
        for(int j=0;j<HEIGHT;j++)
        {
            int dx=i-centerX;
            int dy=j-centerY;
            int radiussquared=dx*dx+dy*dy;
            if(radiussquared<=radius*radius)
            {
                board[i][j]='*';
            }
        }
    }
}
void clearboard()
{
    for(int i=0;i<WIDTH;i++)
    {
        for(int j=0;j<HEIGHT;j++)
        {
            board[i][j]=' ';
        }
    }
}

// main main

int main()
{
    int n;
    while(1)
    {
        cout<<"Game 1 : Black Jack ! "<<endl;
        cout<<"Game 2 : Cows and Bulls ! "<<endl;
        cout<<"Game 3 : Caesar cipher ! "<<endl;
        cout<<"Game 4 : Painting board ! "<<endl;
        cout<<"If you don't want to play key in -1 "<<endl<<endl;
        cout<<"============================="<<endl;
        cout<<"Which game do you want to play? "<<endl;
        cout<<"Type in your choice : ";
        cin>>n;
        if(n==-1) break;

 //111111111111111111111111111111111111111111111111111111111111111111111111111111111

        if(n==1)
        {
            system("cls");
        /*  srand(time(NULL))
            time(0)是返回時間
            <unsigned int>(time(0))是轉換類型，將time從time_t轉成srand可接受的unsigned int
            srand(static_cast<unsigned int>(time(0)))讓每次都會得到不同的隨機變數
        */
        srand(static_cast<unsigned int>(time(0)));
        //先產生隨機洗好的撲克牌
        pair<string, string> deck[DECK_SIZE];
        generateDECK(deck);
        randomDECK(deck);
        //string陣列紀錄玩家跟電腦手上的牌
        pair<string, string> playerHAND[MAX_HAND_SIZE];
        pair<string, string> computerHAND[MAX_HAND_SIZE];

        int playerHANDSIZE=0;
        int computerHANDSIZE=0;
        //玩家跟電腦都先各拿兩張，玩家跟電腦手上牌數增加，未拿走的牌數隨之減少
        playerHAND[playerHANDSIZE++] = deck[--DECK_SIZE];
        computerHAND[computerHANDSIZE++] = deck[--DECK_SIZE];
        playerHAND[playerHANDSIZE++] = deck[--DECK_SIZE];
        computerHAND[computerHANDSIZE++] = deck[--DECK_SIZE];

        cout<<"welcome to the world of Black Jack !"<<endl;
        cout<<endl;
        cout<<"Both of us have two cards now"<<endl<<endl;
        cout<<"It's my turn! Let me see~"<<endl;
        //電腦手上的牌還沒超過18就一直拿牌
        while (countPOINT(computerHAND,computerHANDSIZE) < 19)
        {
            computerHAND[computerHANDSIZE++] = deck[--DECK_SIZE];
            cout<<"I want one more card"<<endl;
        }
        cout<<"OK~ I pass~"<<endl<<endl;
        //電腦抽完後換玩家
        cout<<"It's your turn~"<<endl;
        cout <<"Your card are:";
        printHECK(playerHAND,playerHANDSIZE);
        while(1)
        {
            char choice;
            cout<<"If you want one more card enter'y',otherwise enter'n'"<<endl;
            cin>>choice;

            if(choice=='Y'||choice=='y')
            {
                playerHAND[playerHANDSIZE++] = deck[--DECK_SIZE];
                cout << "Your card are:";
                printHECK(playerHAND,playerHANDSIZE);
            }
            else if(choice=='N'||choice=='n')
            {
                break;
            }
            else
            {
                cout<<"Enter error!!!"<<endl;
            }
        }
        cout<<"============================"<<endl<<endl;
        cout<<"Game Result:"<<endl;
        cout << "My card are:";
        printHECK(computerHAND,computerHANDSIZE);
        cout << "Your card are:";
        printHECK(playerHAND,playerHANDSIZE);

        int playerpoints = countPOINT(playerHAND, playerHANDSIZE);
        int computerpoints = countPOINT(computerHAND, computerHANDSIZE);
        if(playerpoints>21&&computerpoints>21)
        {
            cout << "Both of us lose"<<endl;
        }
        else if(playerpoints>21)
        {
            cout << "You lose~"<<endl;
        }
        else if(computerpoints>21)
        {
            cout << "You win~"<<endl;
        }
        else if(computerpoints>playerpoints)
        {
            cout << "You lose~"<<endl;
        }
        else if(playerpoints>computerpoints)
        {
            cout << "You win~"<<endl;
        }
        else if(computerpoints==playerpoints)
        {
            cout << "This game ended in a tie"<<endl;
        }
        system("pause");
        system("cls");
        }

//222222222222222222222222222222222222222222222222222222222222222222

        if(n==2)
        {
            system("cls");
            srand(time(0)); //﹍て繦诀计贺
            int ans;
            string ansnum;
            while(1)
            {
                ans=rand()%9000+1000; //玻ネΘ繦诀4计
                ansnum=to_string(ans); //盢计锣传才﹃矪瞶
                if((ansnum[0]!=ansnum[1])&&(ansnum[0]!=ansnum[2])&&(ansnum[0]!=ansnum[3])&&(ansnum[1]!=ansnum[2])&&(ansnum[1]!=ansnum[3])&&(ansnum[2]!=ansnum[3]))
                {
                    break;
                }
            }

            string guess;
            int tried=0;
            bool correct=false;

            cout<<"Welcome to Bulls and Cows~"<<endl;
            while(!correct)
            {
                while(1)
                {
                    cout<<"Please input your answer: ";
                    cin>>guess;
                    if((guess[0]==guess[1])||(guess[0]==guess[2])||(guess[0]==guess[3])||(guess[1]==guess[2])||(guess[1]==guess[3])||(guess[2]==guess[3]))
                    {
                        cout<<"Invalid input:( "<<endl;
                    }
                    else
                    {
                        break;
                    }
                }
                tried++;
                int numA=0;
                int numB=0;

                for(int i=0;i<4;i++)
                {
                    if(guess[i]==ansnum[i])
                    {
                        numA++;
                    }
                    else if(ansnum.find(guess[i])!=string::npos)
                    {
                        numB++;
                    }
                }

                cout<<tried<<" . guess is "<<guess[0]<<guess[1]<<guess[2]<<guess[3]<<", get "<<numA<<"A"<<numB<<"B"<<endl;
                if(numA==4)
                {
                    correct=true;
                }
                if(tried>=10) break;
            }
            if(tried>=10)
            {
                cout<<"You are lose, the answer is "<<ansnum<<endl;
            }
            else
            {
                cout<<"Congratulations, the answer is "<<ansnum<<"!!!"<<endl;
            }
            system("pause");
            system("cls");
        }

//33333333333333333333333333333333333333333333333

        if(n==3)
        {
            system("cls");
            ifstream inputFile("encrypt.txt"); //開啟檔案來讀取加密訊息和偏移量
            if(!inputFile.is_open())
            {
                cout<<"Cannnot found encrypt.txt !"<<endl;
                return 1;
            }
            string encryptMessage;
            getline(inputFile, encryptMessage); //讀取整行加密訊息
            cout<<"The encrypted message is: "<<encryptMessage<<endl;
            int offset;
            cout<<"Please type in offset: ";
            cin>>offset;
            cout<<endl;
            cout<<"=========================="<<endl;
            string decryptMessage= decrypt(encryptMessage, offset); //解密訊息
            cout<<"The decrypted message is: "<<decryptMessage<<endl;

            ofstream outputFile("decrypt.txt"); //開啟檔案來輸出解密訊息
            if(outputFile.is_open()) //確認檔案是不是成功開啟
            {
                outputFile<<decryptMessage; //將解密訊息寫入檔案中
                outputFile.close(); //關閉檔案
            }
            else
            {
                cout<<"Cannnot open decrypt.txt to output the words !"<<endl;
            }
            inputFile.close(); //關閉檔案
            system("pause");
            system("cls");
        }

//444444444444444444444444444444444444444444
        if(n==4)
        {
            system("cls");
            blankboard();
            while(1)
        {
        renderboard();
        cout << "There is a 30*10 board! " << endl;
        cout << "0<=x<10 , 0<=y<30" << endl;
        cout << "1. Draw a line" << endl;
        cout << "2. Draw a rectangle" << endl;
        cout << "3. Draw a circle" << endl;
        cout << "4. Clear the board" << endl;
        cout << "5. Quit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            int x1, y1, x2, y2;
            while(1)
            {
                cout << "Enter the starting point (x1, y1): ";
                cin >> x1 >> y1;
                if(x1>10||x1<0||y1>30||y1<0)
                {
                    cout<<"Invalid input"<<endl;
                }
                else
                {
                    break;
                }
            }
            while(1)
            {
                cout << "Enter the ending point (x2, y2): ";
                cin >> x2 >> y2;
                if(x2>10||x2<0||y2>30||y2<0)
                {
                    cout<<"Invalid input"<<endl;
                }
                else
                {
                    break;
                }
            }

            Line(x1, y1, x2, y2);
        }
        else if (choice == 2)
        {
            int x1, y1, x2, y2;
            while(1)
            {
                cout << "Enter the top-left point (x1, y1): ";
                cin >> x1 >> y1;
                if(x1>10||x1<0||y1>30||y1<0)
                {
                    cout<<"Invalid input"<<endl;
                }
                else
                {
                    break;
                }
            }
            while(1)
            {
                cout << "Enter the bottom-right point (x2, y2): ";
                cin >> x2 >> y2;
                if(x2>10||x2<0||y2>30||y2<0)
                {
                    cout<<"Invalid input"<<endl;
                }
                else
                {
                    break;
                }
            }
            Rectangle(x1, y1, x2, y2);
        }
        else if (choice == 3)
        {
            int centerX, centerY, radius;
            while(1)
            {
                cout << "Enter the center point (x, y): ";
                cin >> centerX >> centerY;
                if(centerX>10||centerX<0||centerY>30||centerY<0)
                {
                    cout<<"Invalid input"<<endl;
                }
                else
                {
                    break;
                }
            }

            cout << "Enter the radius: ";
            cin >> radius;
            Circle(centerX, centerY, radius);
        }
        else if (choice == 4)
        {
            clearboard();
        }
        else if (choice == 5)
        {
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
        system("cls");
        }
        system("pause");
        system("cls");
        }
        system("cls");
    }
    return 0;
}
