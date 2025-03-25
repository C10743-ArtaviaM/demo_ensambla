// g++ demo.cpp -o demo -lsfml-graphics -lsfml-window -lsfml-system
// ./demo
// g++ demo.cpp -o demo -lsfml-graphics -lsfml-window -lsfml-system

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <functional>

class Button
{
public:
    Button(float x, float y, float width, float height, const std::string &label)
        : rect(sf::Vector2f(width, height)), text(label, font, 20), isSelected(false)
    {
        rect.setPosition(x, y);
        rect.setFillColor(sf::Color::Cyan);

        text.setPosition(x + (width - text.getLocalBounds().width) / 2, y + (height - text.getLocalBounds().height) / 2);
    }

    void setFont(const sf::Font &font)
    {
        this->font = font;
        text.setFont(font);
        text.setColor(sf::Color::Black);
    }

    bool isClicked(const sf::Vector2i &mousePos) const
    {
        return rect.getGlobalBounds().contains(mousePos.x, mousePos.y);
    }

    void setSelected(bool selected)
    {
        isSelected = selected;
        if (isSelected)
            rect.setFillColor(sf::Color::Green);
        else
            rect.setFillColor(sf::Color::Cyan);
    }

    void draw(sf::RenderWindow &window) const
    {
        window.draw(rect);
        window.draw(text);
    }

    bool getSelected() const { return isSelected; }

public:
    sf::RectangleShape rect;

private:
    sf::Text text;
    sf::Font font;
    bool isSelected;
};

// Clase para Checkbox
class Checkbox : public Button
{
public:
    Checkbox(float x, float y, const std::string &label)
        : Button(x, y, 30, 30, label), checked(false)
    {
        // Agregar un borde para el checkbox
        rect.setOutlineColor(sf::Color::Black);
        rect.setOutlineThickness(2);
    }

    void toggle()
    {
        checked = !checked;
        rect.setFillColor(checked ? sf::Color::Green : sf::Color::Cyan);
    }

    bool isChecked() const { return checked; }

private:
    bool checked;
};

// Menú desplegable
class Dropdown
{
public:
    Dropdown(float x, float y, const sf::Font &font)
        : button(x, y, 200, 50, "Dropdown"), font(font)
    {
        button.setFont(font);
    }

    void addOption(const std::string &label)
    {
        options.push_back(Button(button.rect.getPosition().x, button.rect.getPosition().y + options.size() * 50, 200, 50, label));
        options.back().setFont(font);
    }

    void toggle()
    {
        isOpen = !isOpen;
    }

    bool isClicked(const sf::Vector2i &mousePos)
    {
        if (button.isClicked(mousePos))
        {
            toggle();
            return true;
        }

        for (auto &option : options)
        {
            if (option.isClicked(mousePos))
            {
                std::cout << "Opcion seleccionada: " << option.getSelected() << std::endl;
                toggle(); // Cerrar el dropdown después de seleccionar
                return true;
            }
        }

        return false;
    }

    void draw(sf::RenderWindow &window)
    {
        button.draw(window);

        if (isOpen)
        {
            for (auto &option : options)
                option.draw(window);
        }
    }

private:
    Button button;
    std::vector<Button> options;
    sf::Font font;
    bool isOpen = false;
};

// Clase de Popup
class Popup
{
public:
    Popup(float x, float y, const std::string &message, const sf::Font &font)
        : rect(sf::Vector2f(400, 200)), text(message, font, 20)
    {
        rect.setPosition(x, y);
        rect.setFillColor(sf::Color::White);
        rect.setOutlineThickness(2);
        rect.setOutlineColor(sf::Color::Black);

        text.setPosition(x + (rect.getSize().x - text.getLocalBounds().width) / 2,
                         y + (rect.getSize().y - text.getLocalBounds().height) / 2);
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(rect);
        window.draw(text);
    }

private:
    sf::RectangleShape rect;
    sf::Text text;
};

// Menú básico
class Menu
{
public:
    Menu(float x, float y, const sf::Font &font)
        : button(x, y, 200, 50, "Menu"), font(font)
    {
        button.setFont(font);
    }

    void addOption(const std::string &label)
    {
        options.push_back(Button(button.rect.getPosition().x, button.rect.getPosition().y + options.size() * 50, 200, 50, label));
        options.back().setFont(font);
    }

    void toggle()
    {
        isOpen = !isOpen;
    }

    bool isClicked(const sf::Vector2i &mousePos)
    {
        if (button.isClicked(mousePos))
        {
            toggle();
            return true;
        }

        for (auto &option : options)
        {
            if (option.isClicked(mousePos))
            {
                std::cout << "Opcion del menu seleccionada: " << option.getSelected() << std::endl;
                toggle();
                return true;
            }
        }

        return false;
    }

    void draw(sf::RenderWindow &window)
    {
        button.draw(window);

        if (isOpen)
        {
            for (auto &option : options)
                option.draw(window);
        }
    }

private:
    Button button;
    std::vector<Button> options;
    sf::Font font;
    bool isOpen = false;
};

int main()
{
    // Crear la ventana
    sf::RenderWindow window(sf::VideoMode(800, 600), "Prueba SFML - Interfaz Básica");
    window.setFramerateLimit(60);

    // Cargar fuente
    sf::Font font;
    if (!font.loadFromFile("./../fonts/arial.ttf"))
    {
        std::cout << "No se pudo cargar la fuente." << std::endl;
        return -1;
    }

    // Crear los botones y checkboxes
    Button button1(100, 100, 200, 50, "Boton 1");
    button1.setFont(font);
    Button button2(100, 200, 200, 50, "Boton 2");
    button2.setFont(font);

    Button radioButton1(100, 300, 200, 50, "Radio Button 1");
    radioButton1.setFont(font);
    Button radioButton2(100, 400, 200, 50, "Radio Button 2");
    radioButton2.setFont(font);

    Checkbox checkbox1(100, 500, "Checkbox 1");
    checkbox1.setFont(font);

    // Crear dropdown
    Dropdown dropdown(100, 600, font);
    dropdown.addOption("Opcion 1");
    dropdown.addOption("Opcion 2");
    dropdown.addOption("Opcion 3");

    // Crear Pop-up
    Popup popup(300, 200, "¡Boton 1 Clickeado!", font);

    // Crear Menú
    Menu menu(500, 100, font);
    menu.addOption("Opcion 1");
    menu.addOption("Opcion 2");
    menu.addOption("Opcion 3");

    sf::Text label("Texto de etiqueta", font, 20);
    label.setPosition(100, 50);

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

                if (button1.isClicked(mousePos))
                {
                    button1Clicked = !button1Clicked;
                    std::cout << "Botón 1 clickeado!" << std::endl;
                    popup = Popup(300, 200, "¡Boton 1 Clickeado!", font); // Crear nuevo pop-up al hacer clic
                }

                if (button2.isClicked(mousePos))
                {
                    button2Clicked = !button2Clicked;
                    std::cout << "Boton 2 clickeado!" << std::endl;
                }

                if (radioButton1.isClicked(mousePos))
                {
                    radioButton1.setSelected(true);
                    radioButton2.setSelected(false);
                    std::cout << "Radio Button 1 seleccionado!" << std::endl;
                }

                if (radioButton2.isClicked(mousePos))
                {
                    radioButton1.setSelected(false);
                    radioButton2.setSelected(true);
                    std::cout << "Radio Button 2 seleccionado!" << std::endl;
                }

                if (checkbox1.isClicked(mousePos))
                {
                    checkbox1.toggle();
                    std::cout << "Checkbox 1 " << (checkbox1.isChecked() ? "marcado" : "desmarcado") << std::endl;
                }

                dropdown.isClicked(mousePos);

                // Llamar al menú
                menu.isClicked(mousePos);
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
        checkbox1.draw(window);
        dropdown.draw(window);
        popup.draw(window); // Dibujar el pop-up
        menu.draw(window);  // Dibujar el menú

        // Mostrar todo lo que hemos dibujado
        window.display();
    }

    return 0;
}