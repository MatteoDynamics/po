#include "Osciloscope.h"
#include "Screen.h"

Osciloscope::Osciloscope(Screen& screen)
{
    set_waveform(screen);
}
void Osciloscope::set_waveform(Screen& screen)
{
    waveform.setPrimitiveType(sf::LinesStrip);
    // ...
    waveform.resize(numPoints);
    for (int i = 0; i < numPoints; ++i)
    {
        float x = float(i) / numPoints * screen.get_screen().getSize().x;
        float y = amplitude * sin(frequency * x);
        waveform[i].position = sf::Vector2f(screen.get_screen().getPosition().x + x, screen.get_screen().getPosition().y + screen.get_screen().getSize().y * 0.5 - y);
        waveform[i].color = sf::Color::Yellow;
    }
    wave_count = 0;
    waveforms = nullptr;
}

void Osciloscope :: save_waveform(const std::string& filename)
{

    std::ofstream file;
    std::locale polishLocale("pl_PL.UTF-8");
    file.imbue(polishLocale);

    file.open(filename, std::ostream::out);
    file << "Xpos;Ypos" << std::endl;
    for (int i = 0; i < numPoints; i++)
    {
        if (i < numPoints)
        {
            file << waveform[i].position.x;
        }file << ";";

        if (i < numPoints)
        {
            file << waveform[i].position.y;
        }file << ";";
        file << std::endl;
    }
    file.close();
}