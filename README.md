# 🌿 Estufa Automatizada com Arduino UNO

Um sistema inteligente de **monitoramento ambiental** capaz de medir **luminosidade**, **umidade do solo** e **temperatura**, acionando automaticamente **motores, relés e alertas sonoros** conforme as condições do ambiente.

Este projeto foi desenvolvido para simular uma **mini estufa automatizada**, controlada por sensores e atuadores conectados ao **Arduino UNO**.

---

## 🧩 Componentes Utilizados

| Componente | Função Principal |
|-------------|------------------|
| 🧠 Arduino UNO | Controla todo o sistema |
| ☀️ Sensor LDR | Mede a intensidade da luz ambiente |
| 💧 Sensor de Umidade do Solo | Mede a umidade da terra |
| 🌡️ Sensor TMP36 | Mede a temperatura ambiente |
| ⚙️ Servo Motor 1 | Controla a entrada de luz (janela/cortina) |
| ⚙️ Servo Motor 2 | Controla a irrigação |
| 💡 Relé + Lâmpada | Simula aquecimento conforme temperatura |
| 🔔 Buzzer Piezo | Emite sons de alerta |
| 🔴🟢🔵 LEDs | Indicadores de umidade (seca, ideal, úmida) |

---

## ⚙️ Conexões dos Componentes

| Componente | Pino Arduino |
|-------------|--------------|
| LDR | A0 |
| Sensor Umidade | A1 |
| TMP36 | A2 |
| Servo Luz | D8 |
| Servo Irrigação | D7 |
| LEDs (umidade) | D9, D10, D11 |
| LED Temperatura | D12 |
| Relé | D4 |
| Buzzer | D3 |
| Alimentação Sensores | 5V e GND |

---

## 💡 Funcionamento do Sistema

O sistema é composto por **3 funções principais** que monitoram cada sensor e atuam conforme as condições do ambiente:

---

### 🔆 1️⃣ Controle de Luz — `LDR()`

  void LDR(){
  int leitura = analogRead(A0);
  if (leitura >= 250) {
    servo.write(180);
    tone(buzzer, 1000, 300); // som curto indicando luz forte
  } else {
    servo.write(0);
  }
}

Mede a luminosidade no pino A0.
Se a luz for forte (>=250):
Gira o servo para 180° (fecha a janela/cortina);
Toca um som curto no buzzer.
Se for fraca, o servo volta a 0° (abre a cortina).

💧 2️⃣ Controle de Umidade — UMI()
void UMI(){
  float umidade = analogRead(A1);
  umidade = map(umidade, 0, 1023, 0, 100);
  ...
}


Lê a umidade do solo no pino A1.

Converte a leitura analógica para uma escala de 0% a 100%.

Acende LEDs indicadores:

🔴 Vermelho (D11) → Solo seco (<40%)

🟢 Verde (D9) → Umidade ideal (40–80%)

🔵 Azul (D10) → Solo úmido (>80%)

Quando o solo está muito seco:

O buzzer toca um som de alerta.

O servo2 abre (180°) simulando irrigação.

Quando muito úmido:

Servo fecha (90°) e buzzer silencia.

🌡️ 3️⃣ Controle de Temperatura — TMP36()
void TMP36(){
  float temperatura = analogRead(A2);
  temperatura = map(temperatura, 20, 358, -40, 125);
  ...
}


Lê a temperatura via TMP36 (pino A2).

Converte o valor analógico em graus Celsius.

Se a temperatura:

🔵 <13°C → LED (D12) acende, indicando frio.

🔴 >26°C → Relé ativa a lâmpada e o buzzer toca um som agudo.

Mantém o relé e buzzer desligados em temperatura ideal.

🔊 Buzzer Piezo — tone()

O buzzer é usado para emitir sons rápidos de alerta conforme o evento:

Situação	Frequência	Duração	Descrição
💡 Luz forte	1000 Hz	300 ms	Som curto
🌱 Solo seco	500 Hz	400 ms	Aviso grave
🔥 Temperatura alta	1500 Hz	500 ms	Alerta agudo
🔄 Fluxo de Execução

Setup: define todos os pinos e inicia os servos e Serial Monitor.

Loop: executa ciclicamente as funções:

LDR() → verifica luminosidade

UMI() → mede umidade e aciona irrigação

TMP36() → controla temperatura e relé

Serial Monitor: exibe leituras contínuas dos sensores.
````
  void LDR(){
  int leitura = analogRead(A0);
  if (leitura >= 250) {
    servo.write(180);
    tone(buzzer, 1000, 300); // som curto indicando luz forte
  } else {
    servo.write(0);
  }
}
