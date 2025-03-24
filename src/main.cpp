#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <functional>

// Definimos un Button básico
class Button
{
public:
    Button(float x, float y, float width, float height, const std::string &label)
        : rect(sf::Vector2f(width, height)), text(label, font, 20)
    {
        rect.setPosition(x, y);
        rect.setFillColor(sf::Color::Black);

        // Centrar el texto en el botón
        text.setPosition(x + (width - text.getLocalBounds().width) / 2, y + (height - text.getLocalBounds().height) / 2);
    }

    void setFont(const sf::Font &font)
    {
        this->font = font;
        text.setFont(font);
    }

    bool isClicked(const sf::Vector2i &mousePos) const
    {
        return rect.getGlobalBounds().contains(mousePos.x, mousePos.y);
    }

    void draw(sf::RenderWindow &window) const
    {
        window.draw(rect);
        window.draw(text);
    }

private:
    sf::RectangleShape rect;
    sf::Text text;
    sf::Font font;
};

// Crear una ventana y elementos básicos con SFML
int main()
{
    // Crear la ventana
    sf::RenderWindow window(sf::VideoMode(800, 600), "Prueba SFML - Interfaz Básica");
    window.setFramerateLimit(60);

    // Cargar fuente
    sf::Font font;
    if (!font.loadFromFile("./../fonts/arial.ttf"))
    { // Asegúrate de tener esta fuente en tu carpeta
        std::cout << "No se pudo cargar la fuente." << std::endl;
        return -1;
    }

    // Crear los elementos de la interfaz
    Button button1(100, 100, 200, 50, "Boton 1");
    button1.setFont(font);
    Button button2(100, 200, 200, 50, "Boton 2");
    button2.setFont(font);

    // Investigar que son y funciones.
    Button radioButton1(100, 300, 200, 50, "Radio Button 1");
    radioButton1.setFont(font);
    Button radioButton2(100, 400, 200, 50, "Radio Button 2");
    radioButton2.setFont(font);

    // Definirles los selects
    Button dropdown(100, 500, 200, 50, "Dropdown");
    dropdown.setFont(font);

    sf::Text label("Texto de etiqueta", font, 20);
    label.setPosition(100, 50);

    // Variables para comprobar la interacción con los botones
    bool button1Clicked = false;
    bool button2Clicked = false;

    // Loop principal de la ventana
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                // Verificar si el botón fue clickeado
                if (button1.isClicked(mousePos))
                {
                    button1Clicked = !button1Clicked;
                    std::cout << "Botón 1 clickeado!" << std::endl;
                }

                if (button2.isClicked(mousePos))
                {
                    button2Clicked = !button2Clicked;
                    std::cout << "Botón 2 clickeado!" << std::endl;
                }

                if (radioButton1.isClicked(mousePos))
                {
                    std::cout << "Radio Button 1 seleccionado!" << std::endl;
                }

                if (radioButton2.isClicked(mousePos))
                {
                    std::cout << "Radio Button 2 seleccionado!" << std::endl;
                }

                if (dropdown.isClicked(mousePos))
                {
                    // Seleccion de opciones.
                    std::cout << "Dropdown clickeado!" << std::endl;
                }
            }
        }

        // Limpiar la pantalla
        window.clear(sf::Color::White);

        // Dibujar la interfaz
        window.draw(label);
        button1.draw(window);
        button2.draw(window);
        radioButton1.draw(window);
        radioButton2.draw(window);
        dropdown.draw(window);
        // Definir y aplicar alertas y pop-ups
        // Crear checkboxes
        // Definir un menu

        // Mostrar todo lo que hemos dibujado
        window.display();
    }

    return 0;
}
