# BLDC_Driver

# Pesquisa para Desenvolvimento de Driver de Controle para Motores BLDC

## Objetivo
Para iniciar o desenvolvimento do driver de controle para motores BLDC, primeiro deve-se entender os requisitos mínimos e boas práticas para projetar e construir um driver. 
Dentre os objetivos desse projeto estão: 
- Entender como funciona um driver de acionamento de motores BLDC;
- Quais as técnicas de acionamentos mais usadas em drivers;
- Como realizar o controle de motores BLDC;
- Quais os requisitos mínimos para se realizar o controle de um motor BLDC;
- Quais as principais formas de comunicação de módulos de controle;
- Quais os impactos do chaveamento de alto potência na comunicação;
- Como adotar boas práticas no design do driver;

Com esse estudo, espera-se ser capaz de desenvolver um driver de acionamento e controle de motores BLDC para serem utilizados inicialmente em robôs SSL que possuem BLDC para comandar
rodas omnidirecionais, necessitando de um controle preciso de velocidade e que seja confiável para ser utilizado em jogos da liga. 

---

## 1. **Especificações Iniciais do Projeto**
- **Tipo de Motor:** 
  - O driver será utilizado em motores BLDC com as seguintes caracteristicas:
    - Tensão de operação: 24V
    - Potência nominal: 75W
    - Corrente de pico: 20A
    - Temperatura máxima: 75º
    
- **Alimentação:** 
  - Fonte de alimentação:
    - Bateria de lition:
      - Número de células: 7s
      - Tensão nominal: 25.9V
      - Tensão máxima: 29.4V
      - Tensão mínima: 21.0V
      - Interface: Conectores XT30
  - Os circuitos de carregamento, proteção e manutenção das baterias não consta no escopo do projeto.
  
- **Interface de Comunicação:** 
  - Protocolo principal: UART
    - Baudrate: 1Mbps
    - Modo 8N1 
  - Protocolos alternativos: SPI ou PWM
 
- **Sensores:**
  - É necessário se fazer o sensoriamento de:
    - Corrente
    - Tensão
    - Temperatura
    - RPM   
    - Mag e Giro é opcional (controle).
      
---

## 2. **Requisitos Funcionais**
- **Controle de Velocidade:**
  - Comando via UART* para ajustar RPM.

- **Controle de Posição (Opcional):**
  - Utilizar um sensor Magnético como o AS5600 para controle de posição.

- **Monitoramento:**
  - Telemetria básica:
    - corrente
    - tensão
    - RPM
    - Temperatura
      
- **Eficiência:**
  - No momento não é o foco principal.
  
- **Tamanho e Peso:**
  - Limitações físicas devido à montagem direta no motor. Valores são definido pelo projeto mecânico.


---

## 4. **Ferramentas de Desenvolvimento**
- **Hardware:**
  - Osciloscópio, multímetro e gerador de sinal
  - 

- **Software:**
  - IDEs para programação do microcontrolador: VSCode com ESP-IDF
  - Simuladores para eletrônica: LTSpice
  - Ferramentas de CAD: EasyEDA PRO
    
- **Firmware:**
  - Desenvolvimento de bibliotecas de controle para motores BLDC disponíveis em: a definir 


## 3. **Pesquisa sobre Drivers BLDC**

<details> <sumary> **Para detalhes sobre Drivers de acionamento BLDC** </sumary>


## X. **Referências Técnicas**
- **Datasheets e App Notes:**
  - Drivers BLDC:
  - Microcontroladores: 
  - Sensores Hall:
    
- **Guias de Controle de Motor:**
  - "Field Oriented Control (FOC)":
    
  - Controle trapezoidal para BLDCs:

    
---

## XX. **Etapas do Projeto**
1. **Pesquisa Inicial:**
   - Levantamento de requisitos técnicos.
   - Escolha de componentes e análise de viabilidade.
2. **Prototipagem:**
   - Montagem do circuito básico em protoboard.
   - Testes com motor em baixa potência.
3. **Desenvolvimento do Firmware:**
   - Implementação de controle básico.
   - Adição de funcionalidades de monitoramento.
4. **Teste e Validação:**
   - Verificar desempenho em diferentes cenários.
   - Ajustar parâmetros para otimização.
5. **Projeto Final:**
   - Design da PCB.
   - Construção do módulo integrado e testes finais.


## XXX. **Links Úteis**
- **Documentação de BLDC:**
  - 

- **Comunicação UART:**
  - Exemplos de implementação UART em microcontroladores:
    -   

  
</details>



## 4. **Conclusões sobre componentes Essenciais**
- **Microcontrolador:**
  - Requisitos mínimos: a definir 
    
- **Driver de Potência:**
  - Driver adequado para controlar as fases do motor: a definir 
  - Suporte para controle de corrente e tensão.
  - 
- **Sensores:**
  - O motor utiliza sensores Hall
  - Como usar em controle sensorless
  - Definir os pinos minimos para leitura de sensores: 

- **Ciclo de Controle:**
  - Algoritmos a serem usados (FOC, trapezoidal, sinusoidal): a definir 
  - Taxa de atualização e tempo de resposta necessário: a definir 

- **Proteções:**
  - Implementar proteção contra:
    - Sobrecorrente 
    - Sobretensão
    - Sobretemperatura

- **Conectores e Layout:**
  - Planejar espaço para o conector de bateria.
  - Estudo do formato físico para ser montado no motor diretamente.


---



- **PCB Design:**
  - Para realizar todo projeto desde o nível de esquemáticos até layout do driver, fora utilizado o software *EasyEDA PRO*


<p align="center">
  <strong><span style="font-size: 24px;">Softwares utilizados</span></strong>
</p>
<table align="center" style="text-align: center; border-collapse: collapse;">
  <tr>
    <th>EasyEDA</th>
    <th>LTSpice</th>
    <th>VSCode</th>
    <th>PlatformIO</th>
    <th>ESP-IDF</th>
  </tr>
  <tr>
    <td>
      <img src="https://easyeda.com/images/easyeda-thumbnail.png?id=d5ed1fe5930602975df1" style="height: 100px; object-fit: contain;">
    </td>
    <td>
      <img src="https://images.sftcdn.net/images/t_app-icon-m/p/d55e21eb-857a-4b0e-8403-584ec5ce0543/1490032411/ltspice-icon.jpg" style="height: 100px; object-fit: contain;">
    </td>
    <td>
      <img src="https://code.visualstudio.com/assets/images/code-stable.png" style="height: 100px; object-fit: contain;">
    </td>
    <td>
      <img src="https://cdn.platformio.org/images/platformio-logo.17fdc3bc.png" style="height: 100px; object-fit: contain;">
    </td>
    <td>
      <img src="https://www.espressif.com/sites/all/themes/espressif/images/logo-guidelines/primary-vertical-logo.png" style="height: 100px; object-fit: contain;">
    </td>
  </tr>
  <tr>
    <td><a href="https://easyeda.com">easyeda.com</a></td>
    <td><a href="https://www.analog.com/en/design-center/design-tools-and-calculators/ltspice-simulator.html">LTSpice</a></td>
    <td><a href="https://code.visualstudio.com">code.visualstudio.com</a></td>
    <td><a href="https://platformio.org">platformio.org</a></td>
    <td><a href="https://www.espressif.com/en">Espressif.en</a></td>
  </tr>
</table>



<p align="center">
  <strong><span style="font-size: 24px;">:octocat: Desenvolvedores/Contribuintes :octocat:</span></strong>
</p>
<p align="center">
  <a href="https://github.com/iOsnaaente">
    <img src="https://avatars.githubusercontent.com/u/45924781?v=4" width="115">
    <br><sub>iOsnaente</sub>
  </a>
</p>
