
							
				int aux = auxList.back().first.second;
				for(int i = 0; i < g[aux].size(); i++) {
					if(g[aux][i].first.second == (*it2).first.second) {
						cout << "	..((" << (*it2).first.first << "," << (*it2).first.second << "), " << (*it2).second << ")" << endl;
						auxList.push_back(*it2); //cout << "ok2" << endl;
						mySet.insert(auxList); //cout << "ok3" << endl;
						auxList.pop_back();	//cout << "ok4" << endl;			
					}			
				}	
