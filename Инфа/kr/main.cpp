#include <iostream>
#include <fstream>
#include <thread>
#include <random>

using std::cout, std::endl, std::this_thread::sleep_for;
using namespace std::chrono_literals;
std::ofstream logfile;
									            //		      YOU CAN SET THESE CONSTS WHILE DEBUGING
const int TIME_TO_SLEEP = 1;					//  <======== Animation delay (ms)
const bool PRINT_STEPS = true;					//  <======== Enable / disable animation
const int STEPS_LIMIT =  256;					//  <======== Steps limit for each run
const int N_TESTS = 20;						    //  <======== Number of each test runs (>=100 for statistics)

//	=========================================  YOUR CODE HERE  ==========================================
//	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|
//	v	v	v	v	v	v	v	v	v	v	v	v	v	v	v	v	v	v	v	v	v	v	v	v	v	v

int direction = 0;                              //  <======== Your global values.
bool flag=false;                        //  <======== You can add you functions here.
int moving=0;
char a[4]={'u', 'r', 'd', 'l'};
bool flagbypass=false;
int bypassstep=0;
char bypass[7]={'l','d','d','r','u','u','u'};
bool rock=false;
bool rock_did=true;
int rock_x=1, rock_y=1;
int rock_goal_x, rock_goal_y;
char last_ten[10]={'l','u','r','d','l','u','r','d','l','u'};
char rockstar[72]={'u','u','u','u','u','u','u','u','r','d','d','d','d','d','d','d','d','l','d','d','d','d','d','d','d','d','l','u','u','u','u','u','u','u','u','r','r','r','r','r','r','r','r','r','d','l','l','l','l','l','l','l','l','u','l','l','l','l','l','l','l','l','u','r','r','r','r','r','r','r','r','d'};
bool rockstarflag=true;
int rockstarstep=0;
void Reset()                                    //  <======== You can set or reset you globals
{                                               //            before each test.
	direction = 0;
	rockstarstep=0;
	rock_did=true;
	rockstarflag=true;
}

// void MyOwnFunc(){}   
#include <chrono>
#include <random>
int rand_uns(int min, int max) {
	unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	static std::default_random_engine e(seed);
	std::uniform_int_distribution<int> d(min, max);
	return d(e);
}

char Move(char map[][8], int ant_x, int ant_y, int home_x, int home_y, int sample_x, int sample_y) // <======= YEP, THIS IS IT
{/*
	bool ten=true;
	for (int i = 0; i < 9; i++)
	{
		if (last_ten[i]!=last_ten[i+1])
		{
			ten=false;
		}
	}
	if (ten){
		int move=rand_uns(0, 3);
		return a[move];
	}
	for (int i = 0; i < 9; i++)
	{
		last_ten[i]=last_ten[i+1];
	}*/
	
	//обход камня

	    //часть для заготовленных кусков обхода
    if (flagbypass){
        if (bypassstep<7)
        {
            bypassstep++;
			last_ten[9]=bypass[bypassstep-1];
            return bypass[bypassstep-1];
        }
        else{
            flagbypass=false;
            bypassstep=0;
        }
    }
    //часть для заготовленного одного движения
    if (flag)
    {
        flag=false;
		last_ten[9]=a[moving];
        return a[moving];
    }
	//*из*е* камушки
	for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				if(map[x][y]=='#'){
					rock_x=x;
					rock_y=y;
					rock=true;
				}
			}
			
	}
	if ((rock_x==0 && rock_y==0)||(rock_x==7 && rock_y==0)||(rock_x==0 && rock_y==7)||(rock_x==7 && rock_y==7)){
		rock=false;
	}
	if (rock && rock_did){
		if (rockstarflag){
			if (rockstarstep<72)
			{
				rockstarstep++;
				return rockstar[rockstarstep-1];
			}
			else{
				rockstarflag=false;
			}
		}
		if (map[0][0]=='.'){
			rock_goal_x=0;
			rock_goal_y=0;
		}
		if (map[0][7]=='.'){
			rock_goal_x=0;
			rock_goal_y=7;
		}
		if (map[7][0]=='.'){
			rock_goal_x=7;
			rock_goal_y=0;
		}
		if (map[7][7]=='.'){
			rock_goal_x=7;
			rock_goal_y=7;
		}
		if (rock_x==ant_x)
		{
			if (ant_y+1<rock_y){
				last_ten[9]='r';
				return 'r';
			}
			if (ant_y>rock_y+1){
				last_ten[9]='l';
				return 'l';
			}
			if (ant_y+1==rock_y){
				if (ant_x==0)
				{
					char bypass1[7]={'r','d','l','u','u','r','r'};
					for (int i = 0; i < 7; i++)
					{
						bypass[i]=bypass1[i];
					}
					flagbypass=true;
					rock_did=false;
					last_ten[9]='d';
					return 'd';
				}
				if (ant_x==7)
				{
					char bypass1[7]={'r','u','l','d','d','r','r'};
					for (int i = 0; i < 7; i++)
					{
						bypass[i]=bypass1[i];
					}
					flagbypass=true;
					rock_did=false;
					last_ten[9]='u';
					return 'u';
				}
				else
				{
					char bypass1[7]={'r','d','l','d','r','u','l'};
					for (int i = 0; i < 7; i++)
					{
						bypass[i]=bypass1[i];
					}
					flagbypass=true;
					rock_did=false;
					last_ten[9]='u';
					return 'u';
				}
			}

			if (ant_y==rock_y+1){
				if (ant_x==7)
				{
					char bypass1[7]={'l','u','r','d','d','l','l'};
					for (int i = 0; i < 7; i++)
					{
						bypass[i]=bypass1[i];
					}
					flagbypass=true;
					rock_did=false;
					last_ten[9]='u';
					return 'u';	
				}
				if (ant_x==0){
					char bypass1[7]={'l','d','r','u','u','l','l'};
					for (int i = 0; i < 7; i++)
					{
						bypass[i]=bypass1[i];
					}
					flagbypass=true;
					rock_did=false;
					last_ten[9]='d';
					return 'd';					
				}
				else
				{
					char bypass1[7]={'l','d','r','d','l','u','r'};
					for (int i = 0; i < 7; i++)
					{
						bypass[i]=bypass1[i];
					}
					flagbypass=true;
					rock_did=false;
					last_ten[9]='u';
					return 'u';
				}
			}
		}
		if (rock_y==ant_y)
		{
			if (ant_x+1<rock_x){
				last_ten[9]='d';
				return 'd';
			}
			if (ant_x>rock_x+1){
				last_ten[9]='u';
				return 'u';
			}
			if (ant_x+1==rock_x)
			{
				if(ant_y==0)
				{
					char bypass1[7]={'d','r','u','l','l','d','d'};
					for (int i = 0; i < 7; i++)
					{
						bypass[i]=bypass1[i];
					}
					flagbypass=true;
					rock_did=false;
					last_ten[9]='r';
					return 'r';
				}
				if(ant_y==7)
				{
					char bypass1[7]={'d','l','u','r','r','d','d'};
					for (int i = 0; i < 7; i++)
					{
						bypass[i]=bypass1[i];
					}
					flagbypass=true;
					rock_did=false;
					last_ten[9]='l';
					return 'l';
				}
				else{
					char bypass1[7]={'d','l','u','l','d','r','u'};
					for (int i = 0; i < 7; i++)
					{
						bypass[i]=bypass1[i];
					}
					flagbypass=true;
					rock_did=false;
					last_ten[9]='r';
					return 'r';
				}
			}

			if (ant_x==rock_x+1){
				if (ant_y==0){
					char bypass1[7]={'u','r','d','l','l','u','u'};
					for (int i = 0; i < 7; i++)
					{
						bypass[i]=bypass1[i];
					}
					flagbypass=true;
					rock_did=false;
					last_ten[9]='r';
					return 'r';
				}
				if (ant_y==7){
					char bypass1[7]={'u','l','d','r','r','u','u'};
					for (int i = 0; i < 7; i++)
					{
						bypass[i]=bypass1[i];
					}
					flagbypass=true;
					rock_did=false;
					last_ten[9]='l';
					return 'l';
				}
				else
				{
					char bypass1[7]={'u','l','d','l','u','r','d'};
					for (int i = 0; i < 7; i++)
					{
						bypass[i]=bypass1[i];
					}
					flagbypass=true;
					rock_did=false;
					last_ten[9]='r';
					return 'r';
				}
			}
		}
	}

    //1001 случай у стенки, когда мне камень нужно поставить к стене, чтобы потом доставить к площадке, которая у той же стены
    if (home_y==7 && ant_y==7 && sample_y==6){
        if (ant_x!=0){
            char bypass1[7]={'u','l','l','d','r','u','r'};
            for (int i = 0; i < 7; i++)
            {
                bypass[i]=bypass1[i];
            }
            flagbypass=true;
        }
        else{
            char bypass1[7]={'d','l','l','u','r', 'd', 'r'};
            for (int i = 0; i < 7; i++)
            {
                bypass[i]=bypass1[i];
            }
            flagbypass=true;
        }
    }
    if (home_y==0 && ant_y==0 && sample_y==1){
        if (ant_x!=0){
            char bypass1[7]={'u','r','r','d','l', 'u', 'l'};
            for (int i = 0; i < 7; i++)
            {
                bypass[i]=bypass1[i];
            }
            flagbypass=true;
        }
        else{
            char bypass1[7]={'d','r','r','u','l','d','r'};
            for (int i = 0; i < 7; i++)
            {
                bypass[i]=bypass1[i];
            }
            flagbypass=true;
        }
    }
    if (home_x==7 && ant_x==7 && sample_x==6){
        if (ant_y!=0){
            char bypass1[7]={'l','u','u','r','d','l','d'};
            for (int i = 0; i < 7; i++)
            {
                bypass[i]=bypass1[i];
            }
            flagbypass=true;
        }
        else{
            char bypass1[7]={'r','u','u','l','d','r','d'};
            for (int i = 0; i < 7; i++)
            {
                bypass[i]=bypass1[i];
            }
            flagbypass=true;
        }
    }
    if (home_x==0 && ant_x==0 && sample_x==1){
        if (ant_y!=0){
            char bypass1[7]={'l','d','d','r','u','l','u'};
            for (int i = 0; i < 7; i++)
            {
                bypass[i]=bypass1[i];
            }
            flagbypass=true;
        }
        else{
            char bypass1[7]={'r','d','d','l','u','r','u'};
            for (int i = 0; i < 7; i++)
            {
                bypass[i]=bypass1[i];
            }
            flagbypass=true;
        }
    }
    //самый классный случай, когда все на одной прямой (без учета камней, буду флаг ставить)
    if (ant_x==sample_x && ant_x==home_x){
        if (ant_y+1<sample_y){
			last_ten[9]='r';
            return 'r';
        }
        if (ant_y>sample_y+1){
			last_ten[9]='l';
            return 'l';
        }
        if (ant_y+1==sample_y){
			last_ten[9]='l';
            return 'l';
        }

        if (ant_y==sample_y+1){
			last_ten[9]='r';
            return 'r';
        }
    }
    if (ant_y==sample_y && ant_y==home_y){
        if (ant_x+1<sample_x){
			last_ten[9]='d';
            return 'd';
        }
        if (ant_x+1==sample_x){
			last_ten[9]='u';
            return 'u';
        }
        if (ant_x>sample_x+1){
			last_ten[9]='u';
            return 'u';
        }
        if (ant_x==sample_x+1){
			last_ten[9]='d';
            return 'd';
        }
    }
    //также без учета камней начальный поиск ведра и доставка его на линию с площадкой, с дальнейшей установкой лунохода с ними на одну линию
    if (ant_y<sample_y){
		last_ten[9]='r';
        return 'r';
    }
    if (ant_y>sample_y){
		last_ten[9]='l';
        return 'l';
    }
    if (ant_y==sample_y){
        if (sample_x==home_x){
            flag=true;
            if(ant_x>home_x)
            {
                moving=0;
            }
            else
            {
                moving=2;
            }
            if(sample_y>home_y)
            {
				last_ten[9]='l';
            	return 'l';
            }
            else
            {
				last_ten[9]='r';
            	return 'r';
            }
        }
        if (ant_x+1<sample_x){
			last_ten[9]='d';
            return 'd';
        }
        if (ant_x+1==sample_x){
			last_ten[9]='u';
            return 'u';
        }
        if (ant_x>sample_x+1){
			last_ten[9]='u';
            return 'u';
        }
        if (ant_x==sample_x+1){
			last_ten[9]='d';
            return 'd';
        }
    }
    

    last_ten[9]='r';
	return 'r';
}


//	^	^	^	^	^	^	^	^	^	^	^	^	^	^	^	^	^	^	^	^	^	^	^	^	^	^
//	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|
//	=========================================  YOUR CODE HERE  ==========================================



//	========================================= ! DO NOT TOUCH ! ==========================================
//	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|	|
//	v	v	v	v	v	v	v	v	v	v	v	v	v	v	v	v	v	v	v	v	v	v	v	v	v	v

void ClearLab(char lab[][8])
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			lab[i][j] = '.';
}
void PrintLab(char lab[][8])
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
			printf("%c ", lab[i][j]); // cout << lab[i][j] << ' ';
		printf("\n");// cout << endl;
	}
}
bool MakeLab(char lab[][8], int ax, int ay, int Ox, int Oy, int gx, int gy, int rn, int rx[], int ry[])
{
	ClearLab(lab);
	if ((gx == ax && gy == ay) || (gx == Ox && gy == Oy)) { return false; }

	for (int i=0;i<rn;i++)
		lab[rx[i]][ry[i]] = '#';
	if (ax == Ox && ay == Oy)
		lab[ax][ay] = '@';
	else
	{
		lab[ax][ay] = 'a';
		lab[Ox][Oy] = 'O';
	}
	lab[gx][gy] = '%';
	return true;
}
void CopyLab(char lab[][8], char copy[][8], int* ax, int* ay, int* Ox, int* Oy, int* gx, int* gy)
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			copy[i][j] = lab[i][j];
			switch (copy[i][j])
			{
			case 'a': *ax = i; *ay = j; break;
			case '%': *gx = i; *gy = j;	break;
			case 'O': *Ox = i; *Oy = j;	break;
			case '@': *ax = i; *ay = j; *Ox = i; *Oy = j; break;
			default: break;
			}
		}
}

bool MakeLab(char lab[][8], int ax, int ay, int Ox, int Oy, int gx, int gy, int rn)
{
	int rx[64] = { 0 };
	int ry[64] = { 0 };

	if (!MakeLab(lab, ax, ay, Ox, Oy, gx, gy, 0, rx, ry))
    {
        logfile<<"GEN-ERR";
        return false;
    }


	int count = rn;
	int stop = 16;
	while (count > 0) {
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
			{
				if (lab[i][j] == '.' && rand() % 64 < rn && (abs(i - Ox) + abs(j - Oy) > 2))
				{
					lab[i][j] = '#'; count--;
					if (count == 0) return true;
				}
			}
		stop--;
		if (stop == 0)return false;
	}
	return true;
}

int GoTest(char lab[][8], bool doprint)
{
    logfile<<"#\tNew test... ";
	Reset();
	for (int s = 1; s < STEPS_LIMIT+1; s++)
	{
		if (doprint)
		{
			sleep_for(std::chrono::milliseconds(TIME_TO_SLEEP));
			//system("CLS");
			printf("Step: %d / %d                       \n",s, STEPS_LIMIT);
			PrintLab(lab);
			for (int l = 0; l < 9; l++)
			{
				printf("\r\033[A");
			}
		}
		char copy[8][8];
		int ax, ay, Ox, Oy, gx, gy;
		CopyLab(lab, copy, &ax, &ay, &Ox, &Oy, &gx, &gy);
		char c = Move(copy, ax, ay, Ox, Oy, gx, gy);
		if (c=='x') {logfile<<" terminated at step "<<s<<"!\n"; return -1;} //breaking this ant run
		if (c=='q') {logfile<<" terminated!\n"; return -2;} //breaking this ant run

		int tox = ax, toy = ay, totox = ax, totoy = ay, pullx = ax, pully = ay;
		bool toB = true, totoB = true, pullB = true;
		switch (c)
		{
		case 'u': tox--; totox -= 2; pullx++; toB = (tox >= 0); totoB = (totox >= 0); pullB = (pullx < 8); break;
		case 'd': tox++; totox += 2; pullx--; toB = (tox < 8); totoB = (totox < 8); pullB = (pullx >= 0); break;
		case 'l': toy--; totoy -= 2; pully++; toB = (toy >= 0); totoB = (totoy >= 0); pullB = (pully < 8); break;
		case 'r': toy++; totoy += 2; pully--; toB = (toy < 8); totoB = (totoy < 8); pullB = (pully >= 0); break;
		default: //FAIL
			break;
		}
		if (!toB) continue; //wall
		if (lab[tox][toy] == '.' || lab[tox][toy] == 'O') //simple move or pull
		{
			lab[tox][toy] = (lab[tox][toy] == '.') ? 'a' : '@';
			if (!pullB || lab[pullx][pully] == '.' || lab[pullx][pully] == 'O') { lab[ax][ay] = (lab[ax][ay] == 'a') ? '.' : 'O'; continue; }//simple move
			if (lab[pullx][pully] == '%' && lab[ax][ay] == '@') { logfile<<" done in "<<s<<" steps!\n"; return s; }//DONE with pull
			if (lab[pullx][pully] == '#' && lab[ax][ay] == '@') { lab[ax][ay] = 'O';  continue; } //cant pull # to O
			lab[ax][ay] = lab[pullx][pully]; lab[pullx][pully] = '.'; continue;//pull # or %

		}
		if (lab[tox][toy] == '%')
		{
			if (!totoB || lab[totox][totoy] == '#') continue; //wall or blocked
			if (lab[totox][totoy] == '.') { lab[tox][toy] = 'a'; lab[ax][ay] = (lab[ax][ay] == 'a') ? '.' : 'O'; lab[totox][totoy] = '%'; continue; } //push % to .
			if (lab[totox][totoy] == 'O') { logfile<<" done in "<<s<<" steps!\n"; return s; } //DONE with push
		}
		if (lab[tox][toy] == '#')
		{
			if (!totoB || lab[totox][totoy] != '.') continue; //wall or blocked
			lab[tox][toy] = 'a'; lab[ax][ay] = (lab[ax][ay] == 'a') ? '.' : 'O';; lab[totox][totoy] = '#'; continue;  //push # to .
		}
	}
	logfile<<" fail!\n";
	return -1;
}

void StopAll()
{
    cout << "Terminated!" << endl;
	logfile << "#####\tTerminated!\n";
    logfile.close();
    exit(0);
}

int main()
{
    printf("Starting new Antonina runs!\nSTEPS_LIMIT=%d N_TESTS=%d\n",STEPS_LIMIT,N_TESTS);
    logfile.open ("antlog.txt");
    logfile << "#####\tStarting new Antonina runs!\n#####\tSTEPS_LIMIT="<<STEPS_LIMIT<<"\tN_TESTS="<<N_TESTS<<"\n";
	srand(time(NULL));
	char lab[8][8];
	int rx[64];
	int ry[64];
	int nr = 0;
	int wins;
	int sum;
	int score,wr,as;
	int totalscore = 0;

	//Test 00 	one line not at walls
	logfile << "#####\tStarting Test 00...\n";
	wins = 0; sum = 0;
	for (int i = 0; i < N_TESTS; i++)
	{
		int ax = 1 + rand() % 6, ay = 1 + rand() % 6;
		int gx = ax, gy = ay;
		if (rand() % 2 == 0) while (gx == ax) gx = 1 + rand() % 6;
		else while (gy == ay) gy = 1 + rand() % 6;
		MakeLab(lab, ax, ay, ax, ay, gx, gy, 0);
		//test
		printf("Test 00: %d/%d             \n",i,N_TESTS);
		int res = GoTest(lab, PRINT_STEPS);
		if (res > 0) { wins++; sum += res; }
		else if(res==-2) StopAll();
		printf("\r\033[A");
	}
	score = 100*(wins * STEPS_LIMIT - sum)/ STEPS_LIMIT/ N_TESTS;
	totalscore += score;
	wr = 100 * wins / N_TESTS; as = wins > 0 ? sum / wins : 0;
	printf("Test 00: winrate=%d%% av.steps=%d score=%d\n", wr, as, score);
	logfile << "#####\tTest 00: winrate="<<wr<<"% av.steps=" << as<<" score="<<score<<"\n";

	//Test 01 	no line not at walls
	logfile << "#####\tStarting Test 01...\n";
	wins = 0; sum = 0;
	for (int i = 0; i < N_TESTS; i++)
	{
		int ax = 1 + rand() % 6, ay = 1 + rand() % 6;
		int gx = ax, gy = ay;
		while (gx == ax) gx = 1 + rand() % 6;
		while (gy == ay) gy = 1 + rand() % 6;
		MakeLab(lab, ax, ay, ax, ay, gx, gy, 0);
		//test
		printf("Test 01: %d/%d             \n", i, N_TESTS);
		int res = GoTest(lab, PRINT_STEPS);
		if (res > 0) { wins++; sum += res; }
		else if(res==-2) StopAll();
		printf("\r\033[A");
	}
	score = 100 * (wins * STEPS_LIMIT - sum) / STEPS_LIMIT / N_TESTS;
	totalscore += score;
	wr = 100 * wins / N_TESTS; as = wins > 0 ? sum / wins : 0;
	printf("Test 01: winrate=%d%% av.steps=%d score=%d\n", wr, as, score);
	logfile << "#####\tTest 01: winrate="<<wr<<"% av.steps=" << as<<" score="<<score<<"\n";

	//Test 02 	one line O at wall
	logfile << "#####\tStarting Test 02...\n";
	wins = 0; sum = 0;
	for (int i = 0; i < N_TESTS; i++)
	{
		int ax = 1 + rand() % 6, ay = 1 + rand() % 6;
		if (rand() % 2 == 0) ax = (rand() % 2 == 0) ? 0 : 7;
		else ay = (rand() % 2 == 0) ? 0 : 7;
		int gx = ax, gy = ay;
		if (rand() % 2 == 0) while (gx == ax) gx = rand() % 8;
		else while (gy == ay) gy = rand() % 8;
		MakeLab(lab, ax, ay, ax, ay, gx, gy, 0);
		//test
		printf("Test 02: %d/%d             \n", i, N_TESTS);
		int res = GoTest(lab, PRINT_STEPS);
		if (res > 0) { wins++; sum += res; }
		else if(res==-2) StopAll();
		printf("\r\033[A");
	}
	score = 100 * (wins * STEPS_LIMIT - sum) / STEPS_LIMIT / N_TESTS;
	totalscore += score;
	wr = 100 * wins / N_TESTS; as = wins > 0 ? sum / wins : 0;
	printf("Test 02: winrate=%d%% av.steps=%d score=%d\n", wr, as, score);
	logfile << "#####\tTest 02: winrate="<<wr<<"% av.steps=" << as<<" score="<<score<<"\n";

	//Test 03 	all in corners
	logfile << "#####\tStarting Test 03...\n";
	wins = 0; sum = 0;
	for (int i = 0; i < N_TESTS; i++)
	{
		int ax = (rand() % 2 == 0)?0:7, ay = (rand() % 2 == 0) ? 0 : 7;
		int gx = ax, gy = ay;
		while (gx == ax && gy == ay)
		{
			gx = (rand() % 2 == 0) ? 0 : 7;
			gy = (rand() % 2 == 0) ? 0 : 7;
		}
		MakeLab(lab, ax, ay, ax, ay, gx, gy, 0);
		//test
		printf("Test 03: %d/%d             \n", i, N_TESTS);
		int res = GoTest(lab, PRINT_STEPS);
		if (res > 0) { wins++; sum += res; }
		else if(res==-2) StopAll();
		printf("\r\033[A");
	}
	score = 100 * (wins * STEPS_LIMIT - sum) / STEPS_LIMIT / N_TESTS;
	totalscore += score;
	wr = 100 * wins / N_TESTS; as = wins > 0 ? sum / wins : 0;
	printf("Test 03: winrate=%d%% av.steps=%d score=%d\n", wr, as, score);
	logfile << "#####\tTest 03: winrate="<<wr<<"% av.steps=" << as<<" score="<<score<<"\n";

	//Test 04 	at 1 line with 1 #
	logfile << "#####\tStarting Test 04...\n";
	wins = 0; sum = 0;
	for (int i = 0; i < N_TESTS; i++)
	{
		int ax = rand() % 8, ay = rand() % 8;
		int gx = ax, gy = ay;
		if (rand() % 2 == 0) while (abs(gx - ax) < 2) gx = rand() % 8;
		else while (abs(gy - ay) < 2) gy = rand() % 8;
		rx[0] = (gx + ax) / 2;
		ry[0] = (gy + ay) / 2;
		MakeLab(lab, ax, ay, ax, ay, gx, gy, 1, rx, ry);
		//test
		printf("Test 04: %d/%d             \n", i, N_TESTS);
		int res = GoTest(lab, PRINT_STEPS);
		if (res > 0) { wins++; sum += res; }
		else if(res==-2) StopAll();
		printf("\r\033[A");
	}
	score = 100 * (wins * STEPS_LIMIT - sum) / STEPS_LIMIT / N_TESTS;
	totalscore += score;
	wr = 100 * wins / N_TESTS; as = wins > 0 ? sum / wins : 0;
	printf("Test 04: winrate=%d%% av.steps=%d score=%d\n", wr, as, score);
	logfile << "#####\tTest 04: winrate="<<wr<<"% av.steps=" << as<<" score="<<score<<"\n";

	//Test 05 	not at 1 line with 2 #
	logfile << "#####\tStarting Test 05...\n";
	wins = 0; sum = 0;
	for (int i = 0; i < N_TESTS; i++)
	{
		int ax = rand() % 8, ay = rand() % 8;
		int gx = ax, gy = ay;
		while (gx == ax) gx = rand() % 8;
		while (gy == ay) gy = rand() % 8;
		rx[0] = gx;	ry[0] = ay;
		rx[1] = ax;	ry[1] = gy;
		MakeLab(lab, ax, ay, ax, ay, gx, gy, 2, rx, ry);
		//test
		printf("Test 05: %d/%d             \n", i, N_TESTS);
		int res = GoTest(lab, PRINT_STEPS);
		if (res > 0) { wins++; sum += res; }
		else if(res==-2) StopAll();
		printf("\r\033[A");
	}
	score = 100 * (wins * STEPS_LIMIT - sum) / STEPS_LIMIT / N_TESTS;
	totalscore += score;
	wr = 100 * wins / N_TESTS; as = wins > 0 ? sum / wins : 0;
	printf("Test 05: winrate=%d%% av.steps=%d score=%d\n", wr, as, score);
	logfile << "#####\tTest 05: winrate="<<wr<<"% av.steps=" << as<<" score="<<score<<"\n";

	//Tests 06-09 	not at 1 line with many #
	nr = 4;
	for (int k = 0; k < 4; k++)
	{
        logfile << "#####\tStarting Test 0"<<k+6<<"...\n";
		wins = 0;
		sum = 0;
		for (int i = 0; i < N_TESTS; i++)
		{
			int ax = rand() % 8, ay = rand() % 8;
			int gx = ax, gy = ay;
			while (gx == ax) gx = rand() % 8;
			while (gy == ay) gy = rand() % 8;
            bool done = false;
            while(!done)
			    done = MakeLab(lab, ax, ay, ax, ay, gx, gy, nr);
			//test
			printf("Test 0%d: %d/%d             \n", 6+k, i, N_TESTS);
			int res = GoTest(lab, PRINT_STEPS);
			if (res > 0) { wins++; sum += res; }
			else if(res==-2) StopAll();
			printf("\r\033[A");
		}
		score = 100 * (wins * STEPS_LIMIT - sum) / STEPS_LIMIT / N_TESTS;
		totalscore += score;
		wr = 100 * wins / N_TESTS; as = wins > 0 ? sum / wins : 0;
        printf("Test 0%d: winrate=%d%% av.steps=%d score=%d\n",6+k, wr, as, score);
        logfile << "#####\tTest 0"<<k+6<<": winrate="<<wr<<"% av.steps=" << as<<" score="<<score<<"\n";
		nr *= 2;
	}

	//Test 10 1 block line
	logfile << "#####\tStarting Test 10...\n";
	wins = 0; sum = 0;
	for (int i = 0; i < N_TESTS; i++)
	{
		int ax, ay, gx, gy;
		nr = 8;
		if(rand() % 2 == 0) //vert
		{
			ax = rand() % 8; gx = rand() % 8;
			if (rand() % 2 == 0) {ay = rand() % 2; gy = 6+rand() % 2;}
			else {ay = 6 + rand() % 2; gy = rand() % 2;}
			int y = 2 + rand() % 4;
			for (int ir = 0; ir < 8; ir++) { rx[ir] = ir; ry[ir] = y; }
		}
		else
		{
			ay = rand() % 8; gy = rand() % 8;
			if (rand() % 2 == 0) {ax = rand() % 2; gx = 6 + rand() % 2;}
			else {ax = 6 + rand() % 2; gx = rand() % 2;}
			int x = 2 + rand() % 4;
			for (int ir = 0; ir < 8; ir++) { rx[ir] = x; ry[ir] = ir; }
		}
		MakeLab(lab, ax, ay, ax, ay, gx, gy, nr, rx, ry);
		//test
		printf("Test 10: %d/%d             \n", i, N_TESTS);
		int res = GoTest(lab, PRINT_STEPS);
		if (res > 0) { wins++; sum += res; }
		else if(res==-2) StopAll();
		printf("\r\033[A");
	}
	score = 100 * (wins * STEPS_LIMIT - sum) / STEPS_LIMIT / N_TESTS;
	totalscore += score;
	wr = 100 * wins / N_TESTS; as = wins > 0 ? sum / wins : 0;
	printf("Test 10: winrate=%d%% av.steps=%d score=%d\n", wr, as, score);
	logfile << "#####\tTest 10: winrate="<<wr<<"% av.steps=" << as<<" score="<<score<<"\n";

	//Test 11 2 block lines
	logfile << "#####\tStarting Test 11...\n";
	wins = 0; sum = 0;
	for (int i = 0; i < N_TESTS; i++)
	{
		int ax, ay, gx, gy;
		nr = 16;
		if (rand() % 2 == 0) //vert
		{
			ax = rand() % 8; gx = rand() % 8;
			if (rand() % 2 == 0) { ay = rand() % 2; gy = 6 + rand() % 2; }
			else { ay = 6 + rand() % 2; gy = rand() % 2; }
			int y= 2 + rand() % 3;
			for (int ir = 0; ir < 8; ir++) { rx[ir * 2] = ir; ry[ir * 2] = y; rx[ir * 2 + 1] = ir; ry[ir * 2 + 1] = y + 1; }
		}
		else
		{
			ay = rand() % 8; gy = rand() % 8;
			if (rand() % 2 == 0) { ax = rand() % 2; gx = 6 + rand() % 2; }
			else { ax = 6 + rand() % 2; gx = rand() % 2; }
			int x = 2 + rand() % 3;
			for (int ir = 0; ir < 8; ir++) { rx[ir * 2] = x; ry[ir * 2] = ir; rx[ir * 2 + 1] = x+1; ry[ir * 2 + 1] = ir; }
		}
		MakeLab(lab, ax, ay, ax, ay, gx, gy, nr, rx, ry);
		//test
		printf("Test 11: %d/%d             \n", i, N_TESTS);
		int res = GoTest(lab, PRINT_STEPS);
		if (res > 0) { wins++; sum += res; }
		else if(res==-2) StopAll();
		printf("\r\033[A");
	}
	score = 100 * (wins * STEPS_LIMIT - sum) / STEPS_LIMIT / N_TESTS;
	totalscore += score;
	wr = 100 * wins / N_TESTS; as = wins > 0 ? sum / wins : 0;
	printf("Test 11: winrate=%d%% av.steps=%d score=%d\n", wr, as, score);
	logfile << "#####\tTest 11: winrate="<<wr<<"% av.steps=" << as<<" score="<<score<<"\n";

	//Test 12 3 block lines
    logfile << "#####\tStarting Test 12...\n";
	wins = 0; sum = 0;
	for (int i = 0; i < N_TESTS; i++)
	{
		int ax, ay, gx, gy;
		nr = 24;
		if (rand() % 2 == 0) //vert
		{
			ax = rand() % 8; gx = rand() % 8;
			if (rand() % 2 == 0) { ay = rand() % 2; gy = 6 + rand() % 2; }
			else { ay = 6 + rand() % 2; gy = rand() % 2; }
			int x = 2 + rand() % 2;
			for (int ir = 0; ir < 8; ir++)
				for (int ik = 0; ik < 3; ik++) { rx[ir * 3 + ik] = ir; ry[ir * 3 + ik] = x+ik; }
		}
		else
		{
			ay = rand() % 8; gy = rand() % 8;
			if (rand() % 2 == 0) { ax = rand() % 2; gx = 6 + rand() % 2; }
			else { ax = 6 + rand() % 2; gx = rand() % 2; }
			int y = 2 + rand() % 2;
			for (int ir = 0; ir < 8; ir++)
				for (int ik = 0; ik < 3; ik++) { rx[ir * 3 + ik] = y + ik; ry[ir * 3 + ik] = ir; }
		}
		MakeLab(lab, ax, ay, ax, ay, gx, gy, nr, rx, ry);
		//test
		printf("Test 12: %d/%d             \n", i, N_TESTS);
		int res = GoTest(lab, PRINT_STEPS);
		if (res > 0) { wins++; sum += res; }
		else if(res==-2) StopAll();
		printf("\r\033[A");
	}
	score = 100 * (wins * STEPS_LIMIT - sum) / STEPS_LIMIT / N_TESTS;
	totalscore += score;
	wr = 100 * wins / N_TESTS; as = wins > 0 ? sum / wins : 0;
	printf("Test 12: winrate=%d%% av.steps=%d score=%d\n", wr, as, score);
	logfile << "#####\tTest 12: winrate="<<wr<<"% av.steps=" << as<<" score="<<score<<"\n";

	//Test 13 4 block lines
	logfile << "#####\tStarting Test 13...\n";
	wins = 0; sum = 0;
	for (int i = 0; i < N_TESTS; i++)
	{
		int ax, ay, gx, gy;
		nr = 32;
		if (rand() % 2 == 0) //vert
		{
			ax = rand() % 8; gx = rand() % 8;
			if (rand() % 2 == 0) { ay = rand() % 2; gy = 6 + rand() % 2; }
			else { ay = 6 + rand() % 2; gy = rand() % 2; }
			for (int ir = 0; ir < 8; ir++)
				for (int ik = 0; ik < 4; ik++) { rx[ir * 4 + ik] = ir; ry[ir * 4 + ik] = 2+ik; }
		}
		else
		{
			ay = rand() % 8; gy = rand() % 8;
			if (rand() % 2 == 0) { ax = rand() % 2; gx = 6 + rand() % 2; }
			else { ax = 6 + rand() % 2; gx = rand() % 2; }
			for (int ir = 0; ir < 8; ir++)
				for (int ik = 0; ik < 4; ik++) { rx[ir * 4 + ik] = 2 + ik; ry[ir * 4 + ik] = ir; }
		}
		MakeLab(lab, ax, ay, ax, ay, gx, gy, nr, rx, ry);
		//test
		printf("Test 13: %d/%d             \n", i, N_TESTS);
		int res = GoTest(lab, PRINT_STEPS);
		if (res > 0) { wins++; sum += res; }
		else if(res==-2) StopAll();
		printf("\r\033[A");
	}
	score = 100 * (wins * STEPS_LIMIT - sum) / STEPS_LIMIT / N_TESTS;
	totalscore += score;
	wr = 100 * wins / N_TESTS; as = wins > 0 ? sum / wins : 0;
	printf("Test 13: winrate=%d%% av.steps=%d score=%d\n", wr, as, score);
	logfile << "#####\tTest 13: winrate="<<wr<<"% av.steps=" << as<<" score="<<score<<"\n";

	//end
	cout << "Total score = " << totalscore << endl;
	logfile << "#####\tAll done!\n";
        logfile.close();
	return 0;
}