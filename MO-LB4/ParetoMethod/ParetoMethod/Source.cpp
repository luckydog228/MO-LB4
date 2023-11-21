#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

struct Point { //класс point
    double x;
    double y;

    Point(double xp, double yp) : x(xp), y(yp) {}
};

double manhattanLength(Point p1, Point p2) { //манхетенское расстояние считает
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}
double length = 830; // длина дисплея
double  height = 830; //высота дисплея
void displayParetoGraph(std::vector<Point>& paretoSet, Point utopyPoint, std::vector<std::string> alternative) { //создаём график
    sf::RenderWindow window(sf::VideoMode(length, height), "Pareto");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }


        window.clear(sf::Color::White);

        int x0 = 50;
        int y0 = 50; //точка отсчёта для графика

        sf::Font font;
        font.loadFromFile("D:/Labs/MO4/ArialRegular.ttf"); //загружаем шрифты для точек и осей
        //оси
        sf::Vertex xAxis[] =
        {
            sf::Vertex(sf::Vector2f(x0, length - 20), sf::Color::Black), //начало оси x
            sf::Vertex(sf::Vector2f(height - 130, length - 20), sf::Color::Black) //конец оси x
        };

        sf::Vertex yAxis[] =
        {
            sf::Vertex(sf::Vector2f(x0, height - 20), sf::Color::Black),//начало оси y
            sf::Vertex(sf::Vector2f(x0, height - 580), sf::Color::Black)//конец оси y
        };
        window.draw(xAxis, 2, sf::Lines);
        window.draw(yAxis, 2, sf::Lines); //отрисовка осей
        //подписываем оси
        sf::Text axisXText;
        axisXText.setFont(font);
        axisXText.setCharacterSize(16);
        axisXText.setFillColor(sf::Color::Black);
        axisXText.setString("Appearance");
        axisXText.setPosition(600, 800 - axisXText.getLocalBounds().height);

        sf::Text axisYText;
        axisYText.setFont(font);
        axisYText.setCharacterSize(16);
        axisYText.setFillColor(sf::Color::Black);
        axisYText.setString("Character");
        axisYText.setRotation(0);
        axisYText.setPosition(0, 200);

        window.draw(axisXText);
        window.draw(axisYText);
        //точки отрисовка
        for (int i = 0; i < paretoSet.size(); ++i) {
            sf::CircleShape pointCircle(5.f);
            pointCircle.setFillColor(sf::Color::Magenta);
            pointCircle.setPosition(paretoSet[i].x, paretoSet[i].y);
            window.draw(pointCircle);
            //подписываем точки
            sf::Text pointLabel;
            pointLabel.setFont(font);
            pointLabel.setCharacterSize(12);
            pointLabel.setFillColor(sf::Color::Black);
            pointLabel.setString(alternative[i]);
            pointLabel.setPosition(paretoSet[i].x, paretoSet[i].y - 20);
            window.draw(pointLabel);
        }
        //точка Утопии
        sf::CircleShape utopyCircle(7.f);
        utopyCircle.setFillColor(sf::Color::Green);
        utopyCircle.setPosition(utopyPoint.x, utopyPoint.y);
        window.draw(utopyCircle);
        sf::Text text;
        text.setFont(font);
        text.setString("Utopia");
        text.setCharacterSize(12);
        text.setFillColor(sf::Color::Black);
        text.setPosition(utopyPoint.x + 10, utopyPoint.y - 10);
        window.draw(text);

        window.display();
    }
}

std::string runPareto(std::vector<std::vector<double>>& A,
    std::vector<std::string>& alternative, int ind1, int ind2) {
    Point utopyPoint(500, 300);


    std::vector<Point> paretoSet;
    for (const auto& row : A) {
        Point P(row[ind1], row[ind2]);
        paretoSet.push_back(P);
    }
    std::cout << "Множество Парето: ";
    for (const auto& p : paretoSet) {
        std::cout << "(" << p.x << ", " << p.y << ") ";
    }
    std::cout << std::endl;

    displayParetoGraph(paretoSet, utopyPoint, alternative);

    Point bestPoint = paretoSet[0];
    for (const auto& point : paretoSet) {
        if (manhattanLength(utopyPoint, point) < manhattanLength(utopyPoint, bestPoint)) {
            bestPoint = point;
        }
    }

    int index = 0;
    for (int i = 0; i < A.size(); i++) {
        if (A[i][ind1] == bestPoint.x && A[i][ind2] == bestPoint.y) {
            index = i;
        }
    }

    return alternative[index];

}

int main() {
    std::vector<std::string> alternative = { "Tatyana", "Larisa", "Natalya", "Olga" };

    std::vector<std::vector<double>> A = {
    {300, 500},
    {400, 400},
    {100, 500},
    {200, 700},
    };

    std::string result = runPareto(A, alternative, 0, 1);
    std::cout << "Result: " << result;
    return 0;
}

