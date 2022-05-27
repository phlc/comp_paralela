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

- A grande dificuldade em usar a GPU com o openmp foi como transferir as threads
do cálculo das hashs. para a GPU. 
Primeiro tem a questao do tipo de dados string que não podia ser mapeado. Esse
problema foi resolvido transformando em um arranjo de caracteres. 
No entando, o segundo problema não consiguimos superar: ao enviar para a DPU
utilizando "teams distribute parallel for" tinhamos que usar um for. A saída foi
fazer um for de todos uint32_t posssíveis, [0, 0xffffffff]. O problema é que, 
ao contrário da versão CPU, não foi encontrada uma forma eficiente de interromper
as threads assim que uma hash válida fosse aceita. Assim, a GPU tinha que calcular
todo o intervalo, o que tornou inviável. A opção foi utilizar a gpu apenas para 
cálculo da cstr.

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

