############## Descrição #################

1) Arduino: pasta contendo versões bem preliminares
da integração da biblioteca PSX (Controle Playstation)
e hexaPod (que irá prover as funções de movimentação do robô).

2) Hardware: máscaras para impressão da placa de circuito impresso
da controladora que será utilizada para gerar os sinais lógicos
dos 18 servo motores.

3) Firmware: contém o código da controladora PWM que recebe
as solicitações do Arduino (ângulos desejados para cada um dos 18 motores)
e gera os sinais modulados em largura de pulso para os mesmos.