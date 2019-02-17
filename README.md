# ThermoBeer
Aplicação do ThermoBeer com a framework Qt, a  e o microcontrolador ESP8266.
## O que é o ThermoBeer?

O cenário brasileiro de cervejas artesanais está cada vez mais crescendo. As pessoas estão, não só vendendo, mas produzindo cervejas para seu próprio consumo. Sendo assim, uma comunidade foi construída para a produção das cervejas, de maneira a promover dicas e formas de utilização.

As etapas de produção de uma cerveja são demoradas. Algumas delas são a malteação, a moagem, o resfriamento, a fervura, a mostura, a fermentação e a maturação. Dentre estes estágios, um dos mais complicados é a da fermentação, na qual a maioria dos cervejeiros ficam resfriando o seu balde de cerveja enquanto esta passa pelo processo de fermentação. Este resfriamento é feito por checagem mesmo, e faz-se necessário uma quantidade enorme de tempo para verificar a temperatura do balde de cerveja, de maneira a ter que esquentá-lo ou resfriá-lo manualmente e verificar com um termômetro, colocando na mão mesmo. 

![logo](figuras/icone.png)

Como este processo manual pode realmente durar bastante tempo e paciência destes produtores, surge a proposta do ThermoBeer, que ataca os problemas maiores desta etapa: a checagem da temperatura e o resfriamento. 


## Manual do Usuário

### Como Funciona o ThermoBeer?

A ideia do projeto é que o cervejeiro artesanal possa ter acesso à temperatura da sua cerveja e possa ter controle sobre a refrigeração dela no momento que esteja na sua fase de fermentação. Para isso, será disponibilizado um site no qual haverá as informações da temperatura da cerveja durante o processo, medida por um sensor. A refrigeração será controlada a partir de um relé, no qual é acionado ou desligado pelo usuário a partir de seu comando via web. Também há um software para que o usuário seja avisado diretamente via desktop, para a possibilidade de uso offline. 

### Como adquirir o ThermoBeer?

Se desejas utilizar o software do ThermoBeer e usa uma distribuição Linux ou Mac, basta fazer o download do repositório e executar o arquivo MedTask.pro com o QT Creator. Já para Windows, há a possibilidade de fazer a instalação rápida e prática com o ThermoBeerInstaller, bastando apenas baixar o arquivo .zip presente neste repositório e extrai-lo no seu pc. Em seguida, dentro do instalador, apenas necessitarás de passar por alguns passos simples que demorarão segundos para, em seguida, poder utilizar o ThermoBeer normalmente. 

### Informações técnicas


#### Materiais 

- [ESP8266](https://cdn-shop.adafruit.com/product-files/2471/0A-ESP8266__Datasheet__EN_v4.3.pdf)
- Sensor de Temperatura à Prova D'água [DS18B20](https://datasheets.maximintegrated.com/en/ds/DS18B20.pdf)
 - [Módulo Relé] (http://www.fecegypt.com/uploads/dataSheet/1480848003_2_channel_5v_10a_relay_module.pdf) 5V 

#### O Circuito

![circuito](figuras/circuito.jpg)

Utilizamos o sensor DS18B20 pois este é à prova d'água, facilitando o processo de captura das informações da temperatura da cerveja. Além disso, precisamos do módulo relé de 5V para acionar o refrigerador, a fim de permitir o controle da situação da fermentação pelo usuário. É notável aqui que a ESP8266 é fundamental para todo o processo de alimentação do circuito e da comunicação tanto com a página web quanto com o software para computador, visto que ela é quem passa e recebe as informações para o circuito, sendo o "cérebro" de tudo.

Também vale a pena levantar o ponto de que a ESP8266 precisa estar conectada à uma rede WiFi com internet para poder comunicar-se com a página web. Entretanto, a alternativa offline para este caso é apenas plugar o seu cabo microUSB em uma porta USB do computador, de maneira que o usuário possa obter as informações via serial pelo software. 

#### A Página Web

Esta página web está hospedada gratuitamente no Heroku, uma plataforma cloud que permite o deploy de aplicações para desenvolvedores. Aqui, foi utilizado HTML e CSS, para poder organizar o site, além de JavaScript e Python, para reagir à eventos e fazer a comunicação com o software para computador e para a ESP8266. É notável indicar a importância da biblioteca Flask feita pela comunidade do Python, que é bastante crítica para a realização da comunicação e o deploy do servidor. 

#### O Software para Desktop

Desenvolvemos um software para pc a fim do usuário ter controle da nossa aplicação mesmo sem acesso à internet. Aqui, foi utilizado a framework Qt junto com a IDE Qt Creator. A linguagem utilizada foi o C++ e ainda foi necessário a utilização de XML para editar a parte gráfica do programa. 
