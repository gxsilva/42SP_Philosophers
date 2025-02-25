# Jantar dos filósofos

## Condições
Many philosophers = Many Forks

## Analogias
- Eating -> Processando os dados momento onde o filósofo tem dois garfos
    pode ser o processamento de um arquivos
    servidor manipulando um requisição HTTP
- Thinking -> Esperando até tentar uma nova requisição | filósofo já comeu e está aguardano até o momento de uma nova requisição
    servidor aguardando uma nova requisição
    um processo esperando um evento antes de continunar sua execução
- Sleeping -> tempo de espera antes de tentar consumir novamente,Depois de comer, o filósofo dorme antes de voltar a tentar comer novamente 
    um servidor aplicando um _rate limiting_
    um sistema que implementa _blackoff_ (espera um tempo crescente entre tentativas para evitar sobrecarga)

Eating -> Sleeping -> Thiking = processo básico

o mesmo pode pensar até morrer. XD

## Solução 1 - Dead Lock
A primeira solução envolve cada filósofo pegar um garfo e ficar segurando ele esperando pelo segundo. quando tem os dois garfos em mão ele começar a comer
o grande impasse é quando todos os filósofos ficam segurando um garfo esperando pelo segundo que nunca chega, logo DeadLock

## Solução 2 - Starvation
Esse solução envolve que o filosófo pegue um garfo e logo em seguida se ele não for capaz de pegar o segundo ele devolve o primeiro e aguarda um tempo fixo para tentar
pegar o primeiro e o segundo novamente. nesse caso ele pode morrer de Starvation não por ficar travado mas por não conseguir pegar os dois garfos a tempo para comer

## Solução 3 - Starvation + Random time
Quase igual a primeira porem o tempo de aguardo é um fator aleatório, dificultando assim a possibilidade que de quem filosófo morra de fome, a probabilidade de Starvation é minima no entetando não impossível

## Solução 4 - Mutex(semáforo)
Essa solução envolve a exclusão mutua, ou seja cada filósofo/threadh pode ter acesso a um conteudo compartilhado/macarrão por vez.


a operação de pensar basicamente é colocar um dos threads pra dormir durante um tempo. _think = sleep_


se dois filósofos tentarem pegar o mesmo garfo ocorre o problema de _Race Condition_ levando a comportamentos imprevisiveis, como um filósofo achar que está com os dois garfos quando na realidade não está

## Threads != Processo
Thread é a menor unidade de processamento que pode ser executada dentro de um programa.

Um _processo_ é uma instâcia de um programa em execução, com seu próprio espeço de memória e recursos alocados pelo sistema operacional

Um Thread é uma subdivisão dentro de um processo que compartilha a mesma memória e recursos do processo principal mas pode executar tarefas independemente

### Glossário
- Rate Limiting
- Blackoff
- Race Condition
