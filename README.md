# iot
Este projeto foi feito para meu uso próprio/aprendizagem e envolve Arduino ESP32, Banco de dados,Python e Flask. 



Flask:

endpoint /vendas
A hotmart irá jogar seu webhook quando determinada ação ocorrer na plataforma no endpoint do Flask, que está hospedado na nuvem. Após isso, o flask enviará essa webhook para o meu banco de dados que tenho hospedado na hostgator. 

endpoint raís /
aqui o servidor irá aguardar uma requizição POST com diferents botões cada botão irá gerar um retorno diferente, que será responsável por controlar o arduino e foi apenas para isso que criei. o ultimo valor retornado irá ficar armazenado para o arduino fazer a requisição a hora que quiser.

arduino:

o arduino irá fazer uma requisição a raiz do flask, caso  a resposta da requisição for de código 200(sucesso) ele irá realizar diferentes funções de acordo com o corpo. Então quando o usuário clicar no botão ela irá ser passada diretamente ao arduino se a requisição for ok. Além de limpar o display e colocar a nova requisição de código 200 para manter atualizada. se for de outro código, o ultimo conteudo dentro do lcd não irá atualizar. 

Algumas funções no arduino usam banco de dados enquanto outras não usam conexão com internet. 

a parte mais difícil foi conectar ao banco de dados pois tenho dificuldade em back end.

