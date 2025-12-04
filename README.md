# BlackJack en C++ (Terminal GUI - Windows)

> Un juego de BlackJack completamente desarrollado desde cero en C++, con una interfaz de usuario basada en terminal específicamente diseñada para sistemas Windows.

## 📜 Descripción del Proyecto

Entre las funcionalidades destacadas se incluyen:

- Baraja dinámica con mezcla aleatoria (shuffling).
- Jugador y dealer con lógica independiente.
- Control de flujo del juego: repartir cartas, plantarse, pedir carta, y BlackJack automático.
- Interfaz gráfica mediante una terminal: uso de colores, bordes, animaciones simples y textos alineados.
- Soporte para reiniciar partida y juego continuo sin cerrar la aplicación.

## 🖥️ Tecnologías

- Lenguaje: C++
- Entorno: Consola de Windows (CMD/Powershell)

## 📦 Cómo Clonar

```bash
git clone git@github.com:IsokGta7/Black-Jack.git
cd Black-Jack
```

## 🛠️ Prerrequisitos

- **Sistema operativo:** Windows (consola CMD/Powershell).
- **Compilador:** MinGW (incluido en las distribuciones estándar de Code::Blocks para Windows).
- **IDE recomendado:** [Code::Blocks](https://www.codeblocks.org/downloads/) con toolchain MinGW integrado.

## 🧱 Compilación y Ejecución

1. Abre **Code::Blocks**.
2. Selecciona **File > Open...** y carga el archivo del proyecto `Blackjack.cbp` ubicado en la raíz del repositorio.
3. Presiona **Build** o `F9` para compilar.
4. Ejecuta con **Run** o `Ctrl+F10`. Si la consola se cierra al terminar la partida, vuelve a lanzar el ejecutable desde el IDE.

## 🕹️ Controles en el Juego

- **Flechas arriba/abajo:** navegar en el menú y entre opciones de juego.
- **Enter:** confirmar opción (`Pedir`, `Plantar`, `OK`, etc.).
- **Opciones principales:** *Jugar*, *Instrucciones*, *Créditos* y *Salir*.

## 🖥️ Consideraciones de Plataforma y Codificación

- La interfaz se diseñó para la consola de Windows y ajusta dinámicamente el tamaño de la ventana; en otros sistemas puede no mostrarse correctamente.
- El juego imprime caracteres extendidos (acentos y bordes). Usa una consola configurada con codificación UTF-8 o la página de códigos de Windows que muestre estos caracteres sin artefactos.

## 🔧 Solución de Problemas

- **La ventana se corta o el texto se ve desalineado:** maximiza la consola o aumenta el tamaño de la ventana antes de iniciar.
- **Símbolos extraños en pantalla:** cambia la codificación de la consola a UTF-8 (`chcp 65001`) o a la página de códigos predeterminada que renderice caracteres extendidos.
- **No compila en Code::Blocks:** verifica que el kit MinGW esté instalado/seleccionado y que `Blackjack.cbp` se haya abierto desde la ruta correcta del clon (`Black-Jack`).

## 🖼️ Vista Previa

![Juego BlackJack en ejecución](image.png)
