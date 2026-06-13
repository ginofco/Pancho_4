# Projeto Pancho_4

![Status do Projeto](https://img.shields.io/badge/Status-Desenvolvimento-brightgreen)
![Plataforma](https://img.shields.io/badge/Plataforma-Arduino-00979D)
![Tecnologia](https://img.shields.io/badge/Comunicação-NRF24L01-blue)
![License](https://img.shields.io/badge/Licença-MIT-yellow)

## 📋 Descrição do Projeto

Protótipo de robô controlado remotamente via rádio utilizando módulos transceptores NRF24L01, desenvolvido para participação em eventos de cultura maker, por exemplo Arduino Day. O projeto inclui um chassis com ponte H e dois motores DC com rodas para movimento, com possibilidade de expansão para um braço robótico.

## ✨ Funcionalidades

- Controle remoto via rádio com módulos NRF24L01
- Chassis personalizado impresso em 3D
- Controle de motores DC com ponte H
- Design modular para futuras expansões (braço robótico)

## 🛠️ Tecnologias e Componentes

- **Microcontroladores:** Arduino Uno R3
- **Comunicação:** Módulos NRF24L01
- **Motores:** 2x Motores DC com caixa de redução, servomotores
- **Driver de Motor:** Ponte H L298N ou similar
- **Power:** Bateria LiPo 7.4V ou baterias de litio
- **Produção:** Impressora 3D Ender-3 Pro
- **Design:** FreeCAD, TinkerCAD

## 📁 Estrutura do Projeto

```
Arduino_Day_2026_Robo/
├── 1_Documentacao/          # Documentação, datasheets e referências
├── 2_Design/                # Arquivos de design 3D (FreeCAD e STLs)
├── 3_Firmware/              # Códigos Arduino para todos os dispositivos
├── 4_Hardware/              # Esquemas elétricos e designs de PCB
└── 5_TestesEvidencias/      # Registros de testes, fotos e vídeos
```

## 🚀 Como Usar

### Pré-requisitos

- IDE Arduino
- Biblioteca RF24 (para comunicação NRF24L01)
- FreeCAD (para visualização e edição de modelos)

### Instalação

1. Clone este repositório:
```bash
git clone https://github.com/[seu-usuario]/ArduinoDay2026-RoboRadio.git
```

2. Instale as bibliotecas necessárias na IDE Arduino:
   - RF24 by TMRh20
   - Outras bibliotecas listadas em `3_Firmware/Bibliotecas/`

3. Abra o sketch desejado na pasta `3_Firmware/`

### Upload para o Arduino

1. Conecte o Arduino ao computador
2. Selecione a placa e porta corretas na IDE Arduino
3. Compile e faça upload do código

## 🎮 Como Controlar

[Descreva aqui como operar o robô quando estiver pronto]

## 📸 Fotos do Projeto

*(Adicione fotos do progresso aqui)*

## 📝 Registro de Desenvolvimento

- **Agosto 2025**: Início do projeto, definição de escopo e estrutura
- **Setembro 2025**: Desenvolvimento do chassis e comunicação básica
- **[Adicione novas etapas conforme o progresso]**

## 👥 Autor

- **Gino** - Maker e entusiasta de robótica - [Comunidade Maker RJ]

## 🙌 Agradecimentos

- Comunidade Maker do Rio de Janeiro
- Fabricantes dos componentes e bibliotecas utilizadas
- Organizadores do Arduino Day 2026
- FabLab do PoloMaker (Rio de Janeiro)

## 📄 Licença

Este projeto está sob a licença MIT. Veja o arquivo [LICENSE](LICENSE) para detalhes.

---

**Nota:** Este projeto está em desenvolvimento. Atualizações regulares serão feitas conforme o progresso.
