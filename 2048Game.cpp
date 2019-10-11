#include<iostream>
#include<vector>
#include<fstream>
#include<cstdlib>
#include<string>
#include<cmath>

bool merge_num( std::vector<int> &v,int bi, int ei);
int xytoi(int x, int y, int rowlen);
void rotate_anti_clock(std::vector <int> &v);
void print_grid(const std::vector<int>& v);
bool game_over(const std::vector<int>& v);
void random_number(std::vector<int> &v);

int main(){
  std::vector<int> num;
  std::vector<int> tem;
  for(int i=0;i<4;i++){
    tem.push_back(0);
  }
  std::ifstream infile;
  std::string file;
  std::cout<<"enter initial configuration file name"<<std::endl;
  std::cin>>file;
  infile.open(file.c_str());
  if(!infile.is_open()){
    std::cout<<"the file couldn't be opened, using default start  configuration"<<std::endl;
    for(int i=0;i<15;i++){
      num.push_back(0);
    }
    num.push_back(2);
    for(int i=0;i<4;i++){
      for(int j=0; j<4;j++){
        std::cout<<num[xytoi(i,j,4)]<<"\t";
      }
      std::cout<<std::endl;
    }
  }
  else{
  int n,i=0;

  while(infile>>n){
    num.push_back(n);
    i++;
  }
  print_grid(num);
  }
  while(game_over(num)!=1){
    std::string move;
    std::cin>>move;
    int side = std::sqrt(num.size());
    if(move=="a"){
      int k=0;
      for(int i=0;i<num.size();i=i+side){
      int t =merge_num(num,i,i+side);
      tem[k]= t;
      k++;
      }

      for(int i=0;i<4;i++){
        if(tem[i]!=0){
          random_number(num);
          print_grid(num);
          i=4;
        }
      }
    }

    if(move=="s"){
      for(int i=0;i<3;i++){
        rotate_anti_clock(num);
      }
      int k=0;
      for(int i=0;i<num.size();i=i+side){
      int t =merge_num(num,i,i+side);
      tem[k]= t;
      k++;
      }
      rotate_anti_clock(num);
      for(int i=0;i<4;i++){
        if(tem[i]!=0){
          random_number(num);
          print_grid(num);
          i=4;
        }
      }
    }

    if(move=="w"){
      rotate_anti_clock(num);

      int k=0;
      for(int i=0;i<num.size();i=i+side){
      int t =merge_num(num,i,i+side);
      tem[k]= t;
      k++;
      }
      for(int i=0;i<3;i++){
        rotate_anti_clock(num);
      }
      for(int i=0;i<4;i++){
        if(tem[i]!=0){
          random_number(num);
          print_grid(num);
          i=4;
        }
      }
    }
    if(move=="d"){

      for(int i=0;i<2;i++){
        rotate_anti_clock(num);
      }

      int k=0;
      for(int i=0;i<num.size();i=i+side){
      int t =merge_num(num,i,i+side);
      tem[k]= t;
      k++;
      }
      for(int i=0;i<2;i++){
        rotate_anti_clock(num);
      }
      for(int i=0;i<4;i++){
        if(tem[i]!=0){
          random_number(num);
          print_grid(num);
          i=4;
        }
      }
    }
  }
  std::cout<<"Game over"<<std::endl;

  return 0;
}
bool merge_num( std::vector<int> &v,int bi, int ei){
  std::vector<int> tmp;
  std::vector<int> out;
  int a = (bi);
  while(a<ei){
    if(v[a]!=0){
          tmp.push_back(v[a]);
    }
    a++;
  }

  for(int i=0;i<bi;i++){
     out.push_back(v[i]);
  }
  for(int i=0;i<tmp.size();i++){
    if(i!=tmp.size()-1){
      if(tmp[i]==tmp[i+1]){
      out.push_back(tmp[i]*2);
      i++;
    }
    else{
      out.push_back(tmp[i]);
    }
  }
    else{
      out.push_back(tmp[i]);
    }
  }
  int tem = out.size();
  for(int j=tem;j<ei;j++){
    out.push_back(0);
  }
  for(int j=ei; j<v.size();j++){
    out.push_back(v[j]);
  }
  int i=0;
  while(i<v.size()){
    if(v[i]==out[i]){
      i++;
    }
    else{
      for(int i=0; i<v.size();i++){
        v[i]=out[i];
      }
      return true;}
  }
  return false;
}

int xytoi(int x, int y, int rowlen){
	return x*rowlen+y;
}

void rotate_anti_clock(std::vector <int> &v){
  int side = std::sqrt(v.size());
  std::vector <int> tmp;

      for(int i=side-1;i>=0;i--){
        for(int j=0;j<side;j++){
        tmp.push_back(v[xytoi(j,i,side)]);
        }
      }
    for(int i=0;i<tmp.size();i++){
      v[i]=tmp[i];
    }
}

void print_grid(const std::vector<int>& v){
 int side= std::sqrt(v.size());
  for(int i=0;i<side;i++){
    for(int j=0; j<side;j++){
      std::cout<<v[xytoi(i,j,side)]<<"\t";
    }
    std::cout<<std::endl;
  }
}

bool game_over(const std::vector<int>& v){
  int side = std::sqrt(v.size());

  std::vector <int> tmp;
  for(int i=0;i<v.size();i++){
    tmp.push_back(v[i]);
  }

  for(int j=0; j<4;j++){
    for(int i=0;i<tmp.size();i=i+side){
      bool over = merge_num(tmp,i,i+side);
      if(over == true){
        return false;
      }
    }
      rotate_anti_clock(tmp);
  }
  return true;
}
void random_number(std::vector<int> &v){
  int i=0, a=0;
  std::vector<int> tmp;
  while(a<v.size()){
    if(v[a]==0){
          tmp.push_back(v[a]);
    }
    a++;
  }
  if(tmp.size()!=0){
    while(i<v.size()){
      int random = rand()%v.size();
      if(v[random] ==0){
        v[random]=2;
        i=16;
      }
      else{
        i=0;
      }
    }
  }
}
