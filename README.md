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

- **Sistema operativo:** Windows (consola CMD/Powershell) o cualquier terminal con soporte ANSI (probado en Linux).
- **Compilador:** MinGW en Windows o `g++` con soporte C++17 en sistemas UNIX.
- **IDE recomendado:** [Code::Blocks](https://www.codeblocks.org/downloads/) con toolchain MinGW integrado. También puedes compilar desde línea de comandos con `make`.

## 🧱 Compilación y Ejecución

### En Windows (Code::Blocks)
1. Abre **Code::Blocks**.
2. Selecciona **File > Open...** y carga el archivo del proyecto `Blackjack.cbp` ubicado en la raíz del repositorio.
3. Presiona **Build** o `F9` para compilar.
4. Ejecuta con **Run** o `Ctrl+F10`. Si la consola se cierra al terminar la partida, vuelve a lanzar el ejecutable desde el IDE.

### En Linux/macOS (terminal ANSI)
1. Instala `g++` y `make`.
2. Ejecuta `make` para compilar el juego (`bin/Blackjack`), o `make test` para construir y correr los tests de lógica.
3. Lanza el binario generado desde la terminal.

## 🕹️ Controles en el Juego

- **Flechas arriba/abajo:** navegar en el menú y entre opciones de juego.
- **Enter:** confirmar opción (`Pedir`, `Plantar`, `OK`, etc.).
- **Opciones principales:** *Jugar*, *Instrucciones*, *Créditos* y *Salir*.

## 🖥️ Consideraciones de Plataforma y Codificación

- La interfaz ahora utiliza glifos Unicode (bordes y palos) y fuerza la salida a UTF-8 en Windows para evitar símbolos incorrectos en Windows 10/11.
- El tamaño de ventana sólo se ajusta automáticamente en Windows; en otros sistemas el juego se centra mediante códigos ANSI sin cambiar la resolución.
- Si ves artefactos, valida que la terminal use UTF-8 y que las fuentes incluyan caracteres de caja y naipes.

## 🔧 Solución de Problemas

- **La ventana se corta o el texto se ve desalineado:** maximiza la consola o aumenta el tamaño de la ventana antes de iniciar.
- **Símbolos extraños en pantalla:** cambia la codificación de la consola a UTF-8 (`chcp 65001`) y asegúrate de no mezclar fuentes sin soporte Unicode.
- **No compila en Code::Blocks:** verifica que el kit MinGW esté instalado/seleccionado y que `Blackjack.cbp` se haya abierto desde la ruta correcta del clon (`Black-Jack`).
- **En Linux/macOS:** si el cursor queda visible o la consola no se limpia, valida que estés ejecutando en una terminal con soporte ANSI (p. ej. GNOME Terminal, iTerm2).

## 🖼️ Vista Previa

![Juego BlackJack en ejecución](image.png)
