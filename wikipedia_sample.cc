#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>


void clear_stack(std::stack<std::string> st){
while(!st.empty())
    st.pop();
}


std::vector<std::string> path_make(std::vector<std::string>keiro,std::string mokuteki){
  std::vector<std::string> new_keiro;
  new_keiro.push_back("//");
  for(int i =0;i<keiro.size();i++){
  new_keiro.push_back(keiro[i]);
if(keiro.at(i)== mokuteki) break;
  
}
return(new_keiro);
}

std::vector<std::string> re_path_make(std::vector<std::string>keiro,std::string mokuteki){
  std::vector<std::string> path;
  bool now ;
  std::string key = mokuteki;
  //path.push_back(key);
  std::reverse(keiro.begin(),keiro.end());
  for(int i =0;i<keiro.size();i++){
    if(keiro.at(i)== key) now = true;
    if(now){
    if(keiro.at(i)=="//") {
      key = keiro.at(i-1);
      path.push_back(key);
      //std::cout<<key<<std::endl;
      now = false;
    }
    }
  }
  return(path);
  }

//経路を出力
void answer(std::vector<std::string>keiro,std::string mokuteki,std::string start,std::map<std::string, std::string> pages){
  keiro.push_back(start);
  std::reverse(keiro.begin(),keiro.end());
  for(int i=0;i<keiro.size();i++){
    std::cout<<pages[keiro.at(i)]<<std::endl;
  }

}

//スタート地点のid,ゴール地点のid,<リンク元、リンク先一覧>を受けっとたらdfsして経路を返す
void dfs(std::string start_id,std::string goal_id,std::map<std::string, std::set<std::string> > links,std::map<std::string, std::string> pages){
 std::stack<std::string> no_look;//遷移可能idのスタック
 std::map<std::string, bool> seen;
 std::vector<std::string> route;

 no_look.emplace(start_id); 
 seen[start_id] = true;
 while (no_look.size() != 0) {   // 深さ優先探索
        
        std::string state = no_look.top();  // 現在の状態
        //std::cout<<state<<std::endl;
        route.push_back(state);
        no_look.pop();
        for (auto next : links[state]) {
            if (!seen[next]) {  // 未探索の時のみ行う
                seen[next] = true;
                if(next == goal_id) {
                  //std::cout<<pages[next]<<"owari"<<std::endl;
                }
                no_look.emplace(next);  //次の状態をstackへ格納
               // std::cout<<next<<std::endl;
                route.push_back(next);
            }
        }
        //std::cout<<"_________"<<std::endl;
        route.push_back("//");
    }
     if (seen[goal_id]) {
        std::cout << "yes" << std::endl;
        std::cout << "__________" << std::endl;
        std::vector<std::string> re_path = re_path_make(route,goal_id);
    /*for (size_t i = 0; i < re_path.size(); ++i) {
        std::cout << re_path.at(i) << " .";
    }*/
    answer(re_path,goal_id,start_id,pages);
    } else {
        std::cout << "no" << std::endl;
    }
   
    
}

int main() {
  std::map<std::string, std::string> pages;//<id,word>
  std::map<std::string, std::set<std::string> > links;

  {
    std::ifstream file("data/pages_small.txt");
    std::string data;
    while (std::getline(file, data)) {
      auto index = data.find('\t');
      auto id = data.substr(0, index);
      auto title = data.substr(index + 1, data.size() - id.size() - 1);
      pages[id] = title;
    }
  }

  {
    std::ifstream file("data/links_small.txt");
    std::string data;
    while (std::getline(file, data)) {
      auto index = data.find('\t');
      auto from = data.substr(0, index);
      auto to = data.substr(index + 1, data.size() - from.size() - 1);
      links[from].insert(to);
    }
  }



  std::string start_id , goal_id ,start,goal;
  std::cout<<"スタートの言葉を入れてください"<<std::endl;
  std::cin>>start;
std::cout<<"ゴールの言葉を入れてください"<<std::endl;
  std::cin>>goal;
  for (const auto& page : pages) {
    if (page.second == start) {
      std::cout << page.second << " " << page.first << std::endl;
      start_id = page.first;
      break;
    }
  }
  for (const auto& page : pages) {
    if (page.second == goal) {
      std::cout << page.second << " " << page.first << std::endl;
      goal_id = page.first;
      break;
    }
  }
dfs(start_id,goal_id,links,pages);

  return 0;
}
