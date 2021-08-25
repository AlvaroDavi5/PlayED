# PlayED

por _Álvaro Davi S. Alves_ - **2020101874**

Primeiro trabalho de ```Estrutura de Dados I```


#### Turma de Engenharia da Computação :computer:

### Universidade Federal do Espirito Santo ([UFES](https://ufes.br))


<img src="https://www.ufes.br/sites/all/themes/padrao_ufes/images/marca_ufes.png" alt="logo da ufes" height="150px" width="250px">   

____


- [x] Código criado com conteúdo visto em aula
    - [x] Tipos Abstratos de Dados
    - [x] Estruturas Opacas
    - [x] Ponteiros para Funções
    - [x] Listas Encadeadas
        - [x] Simplesmente Ligadas
        - [x] Duplamente Ligadas
    - [x] Gerenciamento de Memória
    - [x] Modularização
    - [x] Leitura de Arquivos

- [x] Documentar funções, estruturas, constantes e macros nos arquivos header em `include` (comentários multilinha)  
- [x] Documentar trechos complicados do código nos arquivos source em `source` (comentários em uma linha)  
- [x] Criar makefile para compilar os arquivos
- [x] Criar arquivo PDF com documentação separada em:  
- **Introdução:**  
Criação de um programa para gerenciar músicas em playlists e relação de usuários no estilo rede social escrito na linguagem procedural estruturada C utilizando tipos abstratos de dados, modularização, leitura de arquivos, estruturas de dados e gerenciamento de memória.  
- **Implementação:**  
O programa é dividido nos arquivos ```friendship```, ```playlists```, ```users``` e ```utils```, onde a implementação das funções e dos tipos abstratos se encontram em arquivos de extensão _.c_ no diretório <span style="color:#f02c00">_source_</span> e suas definições e protótipos se encontram em arquivos de extensão _.h_ no diretório <span style="color:#426cf5">_include_</span>.  

Abaixo, o diagrama representativo de cada tipo implementado:
![TADs e ED](https://raw.githubusercontent.com/AlvaroDavi5/PlayED-Data_Structures/dev/img/diagram.png)
<br>
<br>
A seguir, alguns exemplos da declaração das funções e sua documentação dentro do código, de forma que fiquem compreensíveis e bem documentadas mesmo utilizando ferramentas de IntelliSense existentes na maioria dos editores de código e IDEs.  
<div align="center">
	<img src="https://raw.githubusercontent.com/AlvaroDavi5/PlayED-Data_Structures/dev/img/main.png" alt="main.c" height="420px"/>
	<br>e
	<img src="https://raw.githubusercontent.com/AlvaroDavi5/PlayED-Data_Structures/dev/img/utils.png" alt="utils.c" width="750px"/>
</div>
<br>
<br>
As principais funções existentes no programa podem explicadas em linguagem natural como:

```
	UsersList * initUsersList() - inicia lista de usuarios vazia
	User * registerUser(char *name) - cria um novo usuário com o nome fornecido

	FriendList * initFriendList() - inicia uma lista de amigos vazia
	Friend * makeFriend(User *usr) - cria um novo elemento para a lista de amigos que aponta para um usuário em específico

	PlaylistList * initPlaylistList() - inicia uma lista de playlists vazia
	Playlist * initPlaylist(char *name) - inicia uma playlist vazia que é um elemento de uma lista e uma lista ao mesmo tempo
	Music * createMusic(char *name, char *artist) - cria uma música com nome e artista fornecidos
```
<br>
<br>

* _Estruturas e TADs Implementados:_  
 A escolha das estruturas de cada TAD foi feita após a análise das funcionalidades pedidas, visando facilidade, clareza e versatilidade para o programa.

 - **Lista de Usuários:** lista individualmente encadeada contendo Tamanho, Primeiro e Último Usuário
   * _Usuário:_ TAD contendo Índice, Nome, Lista de Amigos, Lista de Playlists e Próximo Usuário
 - **Lista de Amigos:** lista individualmente encadeada contendo Tamanho, Primeiro e Último Amigo
   * _Amigo:_ TAD contendo Índice, Usuário e Próximo Amigo
 - **Lista de Playlists:** lista duplamente encadeada contendo Tamanho, Primeira e Última Playlist
   * _Playlist:_ TAD contendo Índice, Nome, Anterior e Próxima Playlist e lista individualmente encadeada contendo Tamanho, Primeira e Última Música
     > _Música:_ TAD contendo Índice, Nome, Artista e Próxima Música

- **Conclusão:**  
O trabalho abordou de forma clara e eficiente o uso de estruturas de dados para os mais diversos fins, explicitando a aplicação de tais estruturas desde os mais simples programas aos mais complexos sistemas.  
As maiores dificuldades encontradas foram no uso dos TADs de forma entrelaçada, no gerenciamento de memória e em formas eficientes de criar algoritmos.  

- **Bibliografia:**  
[listas encadeadas - IME-USP](https://www.ime.usp.br/~pf/algoritmos/aulas/lista.html)  
[singly-linked list - TutorialsPoint](https://www.tutorialspoint.com/data_structures_algorithms/linked_list_program_in_c.htm)  
[dooubly-linked list - GeeksforGeeks](https://www.geeksforgeeks.org/doubly-linked-list/)  

