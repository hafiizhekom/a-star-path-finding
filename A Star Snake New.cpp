#define MAX 10000
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
using namespace std;

int statusjalan=0;
int lebar;
int tinggi;
char map[MAX][MAX];
int h[MAX][MAX];
int g[MAX][MAX];

int xstart; int ystart;
int xgoal; int ygoal;
int xseltemp=-1; int yseltemp=-1;
int seltemp=0;
string closedPath[MAX];
string openPath[MAX];

int y1coba=-1;
int x1coba=-1;
int y0coba=-1;
int x0coba=-1;



void initialMap(){
	for(int i=0;i<=MAX;i++){
		for(int j=0;j<=MAX;j++){
		}
	}
}

int stringtoInt(const char * str){
	int angka = atoi( str );
	return angka;
}

string inttoString(int angka){
	string s = static_cast<ostringstream*>( &(ostringstream() << angka) )->str();
	return s;
}

int checkingLastClosedPath(){
	for(int i=0;i<=MAX;i++){
		if(closedPath[i]==""){
			return i;
		}
	}
}

int checkingLastOpenPath(){
	for(int i=0;i<=MAX;i++){
		if(openPath[i]==""){
			return i;
		}
	}
}

int checkValuesG(int x, int y){
			int jarakx = (xstart-x);
			int jaraky = (ystart-y);
			return jarakx+jaraky;
			
}

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, back_inserter(elems));
    return elems;
}


string mergeString(string y, string x){
	stringstream merge;
	merge << y << "," << x;
	return merge.str();
}

void pushClosedPath(int y, int x){
	string xs = inttoString(x);
	string ys = inttoString(y);
	string closed = mergeString(ys,xs);
	closedPath[checkingLastClosedPath()]=closed;
}

void pushOpenPath(int y, int x){
string xs = inttoString(x);
string ys = inttoString(y);
string open = mergeString(ys,xs);
	openPath[checkingLastOpenPath()]=open;
}

void viewClosedPath(){
	cout << "CLOSED PATH" << endl;
	for(int i=0;i<checkingLastClosedPath();i++){
		
		cout << closedPath[i] << "|";
	}
	cout << endl;
}

void viewOpenPath(){
	cout << "OPEN PATH" << endl;
	for(int i=0;i<checkingLastOpenPath();i++){
		
		cout << openPath[i] << "|";
	}
	cout << endl;
}


void viewH(){
	for(int i=0;i<tinggi;i++){
		for(int j=0;j<lebar;j++){
			cout << "|" << i << ", " << j << ": " << h[i][j] << "|" << endl;
		}	
		cout << endl;
	}
}

void viewG(){
	for(int i=0;i<tinggi;i++){
		for(int j=0;j<lebar;j++){
			cout << "|" << i << ", " << j << ": " << g[i][j] << "|" << endl;
		}	
		cout << endl;
	}
}

	void setH(){
	int jarakx;
	int jaraky;
	for(int i=0;i<tinggi;i++){
		for(int j=0;j<lebar;j++){
			
			
			jarakx = (xgoal-j);
			jaraky = (ygoal-i);
			if(jarakx<0){
				jarakx=jarakx*-1;
			}
			
			if(jaraky<0){
				jaraky=jaraky*-1;
			}
			h[i][j]=(jarakx+jaraky)*10;
		}	
	}
	
	if(ystart>ygoal && xstart==xgoal){
		h[ystart+1][xstart]=h[ystart+1][xstart]+20;
	}
	
	if(xstart>xgoal && ystart==ygoal){
		h[ystart][xstart+1]=h[ystart][xstart+1]+20;
	}
	
	h[ystart][xstart]=0;
	h[ygoal][xgoal]=0;
	
	
}

void buildHalangan(int ypenghalang, int xpenghalang){
	int randtype = rand() % 3;
	if(randtype==0){
		map[ypenghalang][xpenghalang] = 'O';
		map[ypenghalang][xpenghalang+1] = 'O';
		map[ypenghalang][xpenghalang-1] = 'O';
	}else if(randtype==1){
		map[ypenghalang][xpenghalang] = 'O';
		map[ypenghalang+1][xpenghalang] = 'O';
		map[ypenghalang-1][xpenghalang] = 'O';
	}else if(randtype==2){
		map[ypenghalang][xpenghalang] = 'O';
		map[ypenghalang][xpenghalang+1] = 'O';
		map[ypenghalang][xpenghalang-1] = 'O';
		map[ypenghalang+1][xpenghalang] = 'O';
		map[ypenghalang-1][xpenghalang] = 'O';
		map[ypenghalang+1][xpenghalang+1] = 'O';
		map[ypenghalang-1][xpenghalang-1] = 'O';
	}
}

void randomHalangan(){
	int xpenghalang;
	int ypenghalang;
	xpenghalang = (rand() % lebar);
	ypenghalang = (rand() % tinggi);
	
	if(xpenghalang==xstart || xpenghalang==xgoal || ypenghalang==ystart || ypenghalang==ygoal){
		randomHalangan();
	}else{
		buildHalangan(ypenghalang, xpenghalang);
	}
}

void setHalangan(){
	int jumlahpenghalang=0;
	int maxpenghalang;
	if(tinggi>lebar){
		maxpenghalang = tinggi;
	}else if(lebar>tinggi){
			maxpenghalang = lebar;
	}else{
		maxpenghalang = lebar;
	}
	while(jumlahpenghalang<1 || jumlahpenghalang>(lebar*tinggi)){
		cout << "Kadar Penghalang [min:1;max:" << maxpenghalang << "]:";
		cin >> jumlahpenghalang;
	
	}
	
	for(int i=0;i<jumlahpenghalang;i++){
		randomHalangan();
		
		
	}
}

void setGoal(){
	
	
	xgoal = (rand() % lebar);
	
	
	ygoal = (rand() % tinggi);
	
	map[ygoal][xgoal] = '?';
}

void setStart(){
	
	
	xstart = (rand() % lebar);
	
	
	ystart = (rand() % tinggi);
	
	map[ystart][xstart] = '@';
}

void setMap(){
	for(int i=0;i<tinggi;i++){
		for(int j=0;j<lebar;j++){
			map[i][j]='_';
		}	
	}
}

void viewMap(){
	for(int j=0;j<lebar;j++){
			cout << j % 10;
		}	
		cout << endl;
	for(int i=0;i<tinggi;i++){
		
		for(int j=0;j<lebar;j++){
			cout << map[i][j];
		}	
		cout << " -" << i << endl;
	}
}

int checkValueClosedPath(int y, int x){
string xs = inttoString(x);
string ys = inttoString(y);
string strip = ",";
string result=ys+strip+xs;
	for(int i=0;i<MAX;i++){
		if(closedPath[i]==result){
			return i;
		}
	}
	return -1;
}

void deleteOpenPath(int y, int x){
	string xs = inttoString(x);
	string ys = inttoString(y);
	string open = mergeString(ys,xs);
	for(int i=0;i<MAX;i++){
		if(openPath[i]==open){
			openPath[i] = "";
			for(int j=i;j<MAX-1;j++){
				
				openPath[j]=openPath[j+1];
			}
			openPath[MAX-1]="";
		}
	}
}

string checkSmallestOpenPath(){
	int x;
	int y;
	int ytemp;
	int xtemp;
	int temp;
	int value;
	for(int i=0;i<checkingLastOpenPath();i++){
		vector<string> open = split(openPath[i],',');
		x =  stringtoInt(open[1].c_str());
		y =  stringtoInt(open[0].c_str());
		value = g[y][x] + h[y][x];
		if(i==0){
			temp = value;
		}else{
			if(value < temp){
				ytemp=y;
				xtemp=x;
				temp = value;
			}
		}
		//cout << "Smallest["<<y<<","<<x<<"]:" << g[y][x] << "+" << h[y][x]<<endl;
	}
	return mergeString(inttoString(ytemp),inttoString(xtemp));
}



void checkAreaOpenPath(int y, int x){
	if(checkValueClosedPath(y,x+1)==-1){
		if(map[y][x+1]!='O' && map[y][x+1]!='\0'){
			g[y][x+1]=10;
			pushOpenPath(y, x+1);
				
		}
	}
	
	if(checkValueClosedPath(y+1,x)==-1){
		if(map[y+1][x]!='O' && map[y+1][x]!='\0'){
			g[y+1][x]=10;
			pushOpenPath(y+1, x);
		}
	}
	
	if(checkValueClosedPath(y,x-1)==-1){
		
		if(map[y][x-1]!='O' && map[y][x-1]!='\0'){
			g[y][x-1]=10;
			pushOpenPath(y, x-1);
		}
	}
	
	if(checkValueClosedPath(y-1,x)==-1){
		if(map[y-1][x]!='O' && map[y-1][x]!='\0'){
			
			g[y-1][x]=10;
			pushOpenPath(y-1, x);
		}
	}
	
	if(checkValueClosedPath(y-1,x-1)==-1){
		if(map[y-1][x-1]!='O' && map[y-1][x-1]!='\0'){
			g[y-1][x-1]=14;
			pushOpenPath(y-1, x-1);
		}
	}
	
	if(checkValueClosedPath(y+1,x+1)==-1){
		if(map[y+1][x+1]!='O' && map[y+1][x+1]!='\0'){
			g[y+1][x+1]=14;
			pushOpenPath(y+1, x+1);
		}
	}
	
	if(checkValueClosedPath(y-1,x+1)==-1){
		if(map[y-1][x+1]!='O' && map[y-1][x+1]!='\0'){
			g[y-1][x+1]=14;
			pushOpenPath(y-1, x+1);
		}
	}
	
	if(checkValueClosedPath(y+1,x-1)==-1){
		if(map[y+1][x-1]!='O' && map[y+1][x-1]!='\0'){
			g[y+1][x-1]=14;
			pushOpenPath(y+1, x-1);
		}
	}
	
	
	
}

void everyClosedPathcheckOpenPath(){
	vector<string> temp;
	int y;
	int x;
	for(int i=0;i<checkingLastClosedPath();i++){
			temp = split(closedPath[i],',');
			y = stringtoInt(temp[0].c_str());
			x = stringtoInt(temp[1].c_str());
			checkAreaOpenPath(y,x);
	}
}

void selisihJalan(int y1, int x1, int y0, int x0){
	if(y1>y0 && x1 == x0){//atas
		cout << "Bawah" << endl;
	}else if(y1<y0 && x1 == x0){//bawah
		cout << "Atas" << endl;
	}else if(y1==y0 && x1>x0){//kanan
		cout << "Kanan" << endl;
	}else if(y1==y0 && x1<x0){//kiri
		cout << "Kiri" << endl;
	}else if(y1<y0 && x1>x0){//ataskanan
		cout << "Atas Kanan" << endl;
	}else if(y1>y0 && x1>x0){//bawahkanan
		cout << "Bawah Kanan" << endl;
	}else if(y1<y0 && x1<x0){//ataskiri
		cout << "Atas Kiri" << endl;
	}else if(y1>y0 && x1<x0){ //bawahkiri
		cout << "Bawah Kiri" << endl;
	}else{
		cout << "Tidak Diketahui" << endl;
	}
}
int searchingPath(){
	
	int xcoba;
	int ycoba;
	
	vector<string> result;
	everyClosedPathcheckOpenPath();
	
	
	result = split(checkSmallestOpenPath(),',');
	ycoba = stringtoInt(result[0].c_str());
	xcoba = stringtoInt(result[1].c_str());
	
	
	if(seltemp==0){
		y0coba=ycoba;
		x0coba=xcoba;
		//cout << "A" << endl;
		selisihJalan(y0coba, x0coba, ystart, xstart);
	}else if(seltemp==1){
		y1coba=ycoba;
		x1coba=xcoba;
		//cout << "B" << endl;
		selisihJalan(y1coba, x1coba, y0coba, x0coba);
	}else{
		x0coba=x1coba;
		y0coba=y1coba;
		x1coba=xcoba;
		y1coba=ycoba;
		//cout << "C" << endl;
		selisihJalan(y1coba, x1coba, y0coba, x0coba);
	}
	//cout << "Y0 " << y0coba << " - " << x0coba << " X0" << endl;
	//cout << "Y1 " << y1coba << " - " << x1coba << " X1" << endl;
	
	//viewOpenPath();
	seltemp=seltemp+1;
	pushClosedPath(ycoba, xcoba);
	deleteOpenPath(ycoba, xcoba);
	//vector<string> x = split("one:two:three", ',');
	if(ycoba == ygoal && xcoba == xgoal){
		return 1;
	}else{
		searchingPath();
	}
}

void markingPath(){
	vector<string> temp;
	for(int i=0;i<checkingLastOpenPath();i++){
		temp = split(openPath[i], ',');
		int y = stringtoInt(temp[0].c_str());
		int x = stringtoInt(temp[1].c_str());
		map[y][x]='#';
	}
	
	for(int i=0;i<checkingLastClosedPath();i++){
		temp = split(closedPath[i], ',');
		int y = stringtoInt(temp[0].c_str());
		int x = stringtoInt(temp[1].c_str());
		if(x!=xgoal || y!=ygoal){
			if(x!=xstart || y!=ystart){
				map[y][x]='X';
			}	
		}
		
	}
}

void titleGame(){
	cout << "==============================================" << endl;
	cout << "=                    SNAKE                   =" << endl;
	cout << "=                    GAMES                   =" << endl;
	cout << "==============================================" << endl;
}

void infoGame(){
	cout << "==============================================" << endl;
	cout << "=                 Information                =" << endl;
	cout << "==============================================" << endl;
	cout << "Halangan: O"<<endl;
	cout << "Snake: *"<<endl;
	cout << "Goal: ?"<<endl;
	cout << "Start: @"<<endl;
	cout << "Goal: " << ygoal << " - " << xgoal << endl;
	cout << "Start: " << ystart << " - " << xstart << endl;
	cout << "==============================================" << endl;
	cout << endl;
}

void menuGame(){
	cout << "==============================================" << endl;
	cout << "=                    Menu                    =" << endl;
	cout << "==============================================" << endl;
	cout << "play - mainkan game" << endl;
	cout << "solve - pecahkan solusi game" << endl;
	cout << "exit - keluar" << endl;
}

void solvePath(){
	pushClosedPath(ystart, xstart);
	cout << "==============================================" << endl;
	cout << "=                    Langkah                 =" << endl;
	cout << "==============================================" << endl;
	searchingPath();
	cout << endl << endl;
	//viewClosedPath();
	markingPath();
	viewMap();
}


void menuPlay(){
	cout << "Menu Gerak" << endl;
	cout << "==========" << endl;
	cout << "atas - Jalan Atas" << endl;
	cout << "bawah - Jalan Bawah" << endl;
	cout << "kiri - Jalan Kiri" << endl;
	cout << "kanan - Jalan Kanan" << endl;
	cout << "ataskanan - Jalan Serong Atas Kanan" << endl;
	cout << "ataskiri - Jalan Serong Atas Kiri" << endl;
	cout << "bawahkanan - Jalan Serong Bawah Kanan" << endl;
	cout << "bawahkiri - Jalan Serong Bawah Kiri" << endl;
}

void setSnakePenetration(int ypos, int xpos){
	if(map[ypos][xpos]=='O'){
		
	}else{
		map[ypos][xpos]='_';
	}
}

string jalanAtas(int ypos, int xpos){
	if(map[ypos-1][xpos]=='O'){
			cout << "==================================" << endl;
			cout << "=        Tidak Bisa Jalan        =" << endl;
			cout << "==================================" << endl;
			return inttoString(ypos)+"-"+inttoString(xpos);
		}else{
			map[ypos-1][xpos] = map[ypos][xpos];
			map[ypos][xpos] = '*';
			setSnakePenetration(ypos+1, xpos);
			setSnakePenetration(ypos, xpos+1);
			setSnakePenetration(ypos, xpos-1);
			setSnakePenetration(ypos+1, xpos+1);
			setSnakePenetration(ypos+1, xpos-1);
			setSnakePenetration(ypos-1, xpos+1);
			setSnakePenetration(ypos-1, xpos-1);
			
		return inttoString(ypos-1)+"-"+inttoString(xpos);
		}
}

string jalanAtasKanan(int ypos, int xpos){
	if(map[ypos-1][xpos+1]=='O'){
			cout << "==================================" << endl;
			cout << "=        Tidak Bisa Jalan        =" << endl;
			cout << "==================================" << endl;
			return inttoString(ypos)+"-"+inttoString(xpos);
		}else{
			map[ypos-1][xpos+1] = map[ypos][xpos];
			map[ypos][xpos] = '*';
			setSnakePenetration(ypos-1, xpos); //atas
			setSnakePenetration(ypos+1, xpos); //bawah
			setSnakePenetration(ypos, xpos+1); //kanan
			setSnakePenetration(ypos, xpos-1); //kiri
			setSnakePenetration(ypos+1, xpos+1);//bawahkanan
			setSnakePenetration(ypos+1, xpos-1);//bawahkiri
			//setSnakePenetration(ypos-1, xpos+1);//ataskanan
			setSnakePenetration(ypos-1, xpos-1);//ataskiri
			
		return inttoString(ypos-1)+"-"+inttoString(xpos+1);
		}
}

string jalanAtasKiri(int ypos, int xpos){
	if(map[ypos-1][xpos-1]=='O'){
			cout << "==================================" << endl;
			cout << "=        Tidak Bisa Jalan        =" << endl;
			cout << "==================================" << endl;
			return inttoString(ypos)+"-"+inttoString(xpos);
		}else{
			map[ypos-1][xpos-1] = map[ypos][xpos];
			map[ypos][xpos] = '*';
			setSnakePenetration(ypos-1, xpos); //atas
			setSnakePenetration(ypos+1, xpos); //bawah
			setSnakePenetration(ypos, xpos+1); //kanan
			setSnakePenetration(ypos, xpos-1); //kiri
			setSnakePenetration(ypos+1, xpos+1);//bawahkanan
			setSnakePenetration(ypos+1, xpos-1);//bawahkiri
			setSnakePenetration(ypos-1, xpos+1);//ataskanan
			//setSnakePenetration(ypos-1, xpos-1);//ataskiri
			return inttoString(ypos-1)+"-"+inttoString(xpos-1);
		}
}

string jalanBawahKanan(int ypos, int xpos){
	if(map[ypos+1][xpos+1]=='O'){
			cout << "==================================" << endl;
			cout << "=        Tidak Bisa Jalan        =" << endl;
			cout << "==================================" << endl;
			return inttoString(ypos)+"-"+inttoString(xpos);
		}else{
			map[ypos+1][xpos+1] = map[ypos][xpos];
			map[ypos][xpos] = '*';
			setSnakePenetration(ypos-1, xpos); //atas
			setSnakePenetration(ypos+1, xpos); //bawah
			setSnakePenetration(ypos, xpos+1); //kanan
			setSnakePenetration(ypos, xpos-1); //kiri
			//setSnakePenetration(ypos+1, xpos+1);//bawahkanan
			setSnakePenetration(ypos+1, xpos-1);//bawahkiri
			setSnakePenetration(ypos-1, xpos+1);//ataskanan
			setSnakePenetration(ypos-1, xpos-1);//ataskiri
			return inttoString(ypos+1)+"-"+inttoString(xpos+1);
		}
}



string jalanBawahKiri(int ypos, int xpos){
	if(map[ypos+1][xpos-1]=='O'){
			cout << "==================================" << endl;
			cout << "=        Tidak Bisa Jalan        =" << endl;
			cout << "==================================" << endl;
			return inttoString(ypos)+"-"+inttoString(xpos);
		}else{
			map[ypos+1][xpos-1] = map[ypos][xpos];
			map[ypos][xpos] = '*';
			setSnakePenetration(ypos-1, xpos); //atas
			setSnakePenetration(ypos+1, xpos); //bawah
			setSnakePenetration(ypos, xpos+1); //kanan
			setSnakePenetration(ypos, xpos-1); //kiri
			setSnakePenetration(ypos+1, xpos+1);//bawahkanan
			//setSnakePenetration(ypos+1, xpos-1);//bawahkiri
			setSnakePenetration(ypos-1, xpos+1);//ataskanan
			setSnakePenetration(ypos-1, xpos-1);//ataskiri
			
		return inttoString(ypos+1)+"-"+inttoString(xpos-1);
		}
}


string jalanBawah(int ypos, int xpos){
	if(map[ypos+1][xpos]=='O'){
			cout << "==================================" << endl;
			cout << "=        Tidak Bisa Jalan        =" << endl;
			cout << "==================================" << endl;
			return inttoString(ypos)+"-"+inttoString(xpos);
		}else{
			map[ypos+1][xpos] = map[ypos][xpos];
			map[ypos][xpos] = '*';
			setSnakePenetration(ypos-1, xpos);
			setSnakePenetration(ypos, xpos+1);
			setSnakePenetration(ypos, xpos-1);
			setSnakePenetration(ypos+1, xpos+1);
			setSnakePenetration(ypos+1, xpos-1);
			setSnakePenetration(ypos-1, xpos+1);
			setSnakePenetration(ypos-1, xpos-1);
			
	return inttoString(ypos+1)+"-"+inttoString(xpos);
		}
}

string jalanKanan(int ypos, int xpos){
	if(map[ypos][xpos+1]=='O'){
			cout << "==================================" << endl;
			cout << "=        Tidak Bisa Jalan        =" << endl;
			cout << "==================================" << endl;
			return inttoString(ypos)+"-"+inttoString(xpos);
		}else{
			map[ypos][xpos+1] = map[ypos][xpos];
			map[ypos][xpos] = '*';
			setSnakePenetration(ypos, xpos-1);
			setSnakePenetration(ypos+1, xpos);
			setSnakePenetration(ypos-1, xpos);
			setSnakePenetration(ypos+1, xpos-1);
			setSnakePenetration(ypos-1, xpos-1);
			setSnakePenetration(ypos+1, xpos+1);
			setSnakePenetration(ypos-1, xpos+1);
			return inttoString(ypos)+"-"+inttoString(xpos+1);
		}
	
}

string jalanKiri(int ypos, int xpos){
	if(map[ypos][xpos-1]=='O'){
			cout << "==================================" << endl;
			cout << "=        Tidak Bisa Jalan        =" << endl;
			cout << "==================================" << endl;
			return inttoString(ypos)+"-"+inttoString(xpos);
		}else{
			map[ypos][xpos-1] = map[ypos][xpos];
			map[ypos][xpos] = '*';
			setSnakePenetration(ypos, xpos+1);
			setSnakePenetration(ypos+1, xpos);
			setSnakePenetration(ypos-1, xpos);
			setSnakePenetration(ypos+1, xpos-1);
			setSnakePenetration(ypos-1, xpos-1);
			setSnakePenetration(ypos+1, xpos+1);
			setSnakePenetration(ypos-1, xpos+1);
			return inttoString(ypos)+"-"+inttoString(xpos-1);
		}
	
}

void checkingPlayCommand(){
	
}

void playPath(){
	int xposition;
	int yposition;
	string newJalan;
	vector<string> tempJalan;
	xposition = xstart;
	yposition = ystart;
	map[ystart][xstart]='*';
	
	string command;
	int status = 0;
	do{
		
		if(yposition == ygoal && xposition == xgoal){
			cout << "Finish" << endl;
			break;
		}
		cout << endl << endl;
		menuPlay();
		cout << "Gerak: ";
		cin >> command;
		system("cls");
		
		if(command=="atas"){
			newJalan = jalanAtas(yposition, xposition);
		}else if(command=="bawah"){
			newJalan = jalanBawah(yposition, xposition);
		}else if(command=="kanan"){
			newJalan = jalanKanan(yposition, xposition);
		}else if(command=="kiri"){
			newJalan = jalanKiri(yposition, xposition);
		}else if(command=="ataskanan"){
			newJalan = jalanAtasKanan(yposition, xposition);
		}else if(command=="ataskiri"){
			newJalan = jalanAtasKiri(yposition, xposition);
		}else if(command=="bawahkanan"){
			newJalan = jalanBawahKanan(yposition, xposition);
		}else if(command=="bawahkiri"){
			newJalan = jalanBawahKiri(yposition, xposition);
		}else{
			cout << "==================================" << endl;
			cout << "=     Jalan Tidak Diketahui      =" << endl;
			cout << "==================================" << endl;
			
			cout << endl;
			cout << endl;
		}
		
		tempJalan = split(newJalan,'-');
		yposition = stringtoInt(tempJalan[0].c_str());
		xposition = stringtoInt(tempJalan[1].c_str());
		
		
		viewMap();
		
	}while(status=1);
}

int main(){
	srand(time(NULL));
	string command;
	
	
	do{
	system("cls");
	titleGame();
	cout << "Lebar Area [min: 10;max:70]: ";
	cin >> lebar;
	cout << "Tinggi Area [min:10;max:100]: ";
	cin >> tinggi;
	}while(lebar > 70 || tinggi > 100 || lebar < 10 || tinggi < 10);
	
	setMap();
	setHalangan();
	setStart();
	setGoal();
	setH();
	cout << endl;
	cout << endl;

	
	
	cout << endl;
	cout << endl;
	infoGame();
	do{
		system("cls");
		viewMap();
		infoGame();
		menuGame();
		cout << "command:";
		cin >> command;
		if(command=="play"){
			system("cls");
			viewMap();
			playPath();
			break;
		}else if(command=="solve"){
			system("cls");
			solvePath(); //Menyelesaikan dengan A*
			cout << endl << endl;
			cout << endl << endl;
			cout << "==============================================" << endl;
			cout << "=               Terima Kasih                 =" << endl;\
			cout << "=                hafiizhekom                 =" << endl;
			cout << "==============================================" << endl;
			cout << endl << endl;
			break;
		}
	}while(command!="exit");
	
	
	getch();
	
	
	
	
}
