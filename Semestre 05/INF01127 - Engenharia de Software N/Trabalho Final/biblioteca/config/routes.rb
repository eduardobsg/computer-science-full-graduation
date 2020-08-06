Biblioteca::Application.routes.draw do
  resources :multas

  resources :emprestimos

  resources :items
   
  resources :item_tipos

  resources :pessoas

  resources :pessoa_tipos
  
 root :to => "items#index"
  
end
