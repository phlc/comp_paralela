Projeto 02 

Ana Laura Fernandes
Larissa Domingues Gomes
Pedro Henrique Lima Carvalho
Pedro Henrique Reis
Tárcila Fernanda


Tempo Programa Serial:

Mining block 1...
Block mined: 000000587ffd51af343fd25e8c78795e6f7fcb65c6dd75c0df5a03b6144be0d1
Mining block 2...
Block mined: 0000008efb7cf3e633608725ba41e1a089dcd4d8610d02e0f26ccbc0da6d18c0
Mining block 3...
Block mined: 000000863d265a5c9c27c690460e0337208f1f6a3d63814de6a8e2d1fef88782

real  13m43.656s
user  13m43.307s
sys   0m0.032s

Tempo Programa Openmp CPU:

Mining block 1...
Block mined: 000000fe9659ce9438db80d7753070d9997b509fb16ed8a5f1cff80f13be9ec7
Mining block 2...
Block mined: 000000affde68d5723c4c50ea469e7b9ef65be66aa5ccb225deec1aa9d7fe078
Mining block 3...
Block mined: 000000ba832504aa7d698f922e2fef0e8a42902e6a11930363584e8e822375f8

real  2m4.864s
user  8m18.577s
sys   0m0.052s


Tempo Programa Openmp GPU:

Obs: Até a parte de mapear todas as variáveis para gpu e mandar chuncks por vez
foi feito.
Mas a grande dificuldade está em mapear para a gpu toda a função de calcular
a hash. Assim, optamos por mapear para a gpu o for anterior

Mining block 1...
Block mined: 000000c065f96d522875952c5dea74abfe273904a4ad6b45f1dda149019d7839
Mining block 2...
Block mined: 000000747f9dbb33e38397087472b4b72968d364cf0f30018421065ce21f1fc6
Mining block 3...
Block mined: 00000089e83b3ec88af4de09934555937bb0a8eafc96d4b7c6bb065fc88baa24

real  2m52.290s
user  9m9.827s
sys   0m0.778s


Tempo Programa Cuda:

Obs: ao contrário da versão openmp, foi possível encontrar o kernel do sha para cuda

Mining block 1...
-----------Block 1-----------
Nonce: L4c6BnBcDWGFpaIvX1xx
Hash: 000000cd54fce9308804fae75bee779543167b2e429b7683a538e1fd57641fd0
Previous Hash: 019dc9ae4bf3bc16642b07c6e4794d08c15e33418fad7f91879b8238b352dc1a
Data: Block 1 Data
Time: 1653703542
Mining block 2...
-----------Block 2-----------
Nonce: lr4KZuLlavZs5xZ6ApUY
Hash: 00000056ceb87b9f56c7755c1bf9803a7f7d3759132a4b66d32c14edfad55cd1
Previous Hash: 000000cd54fce9308804fae75bee779543167b2e429b7683a538e1fd57641fd0
Data: Block 2 Data
Time: 1653703543
Mining block 3...
-----------Block 3-----------
Nonce: v1Htz8uvIFUFbibrt1GA
Hash: 0000002d3ff764b3c7449dba1b74aa7890d833b03fe83ea253ab6a43ff0c5678
Previous Hash: 00000056ceb87b9f56c7755c1bf9803a7f7d3759132a4b66d32c14edfad55cd1
Data: Block 3 Data
Time: 1653703545

real  0m7.079s
user  0m4.610s
sys   0m2.374s


