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
    if (file.fail())
    {
        throw std::exception();
    }
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

void Osciloscope::draw(sf::RenderWindow& window)
{
    window.draw(waveform);
}
void Osciloscope::set_amplitude(float amp, Screen& screen)
{
    amplitude = amp;
    set_waveform(screen);
    std::cout << "osc amp: " << amplitude << std::endl;
}

void Osciloscope::set_frequency(float freq, Screen& screen)
{
    frequency = freq;
    set_waveform(screen);
    std::cout << "osc freq: " << frequency << std::endl;
}

//WAVEFORM ALOCATION
void Osciloscope::add_new_function()
{
    if (wave_count >= 3)
    {
        std::cerr << "Max wave_count is 3" << std::endl;
        return;
    }
    wave_count++;
    sf::VertexArray* tmp;
    tmp = new sf::VertexArray[wave_count];
    if (tmp == NULL)
    {
        std::cerr << "Not enough memory" << std::endl;
        return;
    }
    for (int i = 0; i < wave_count - 1; i++)
    {
        tmp[i] = waveforms[i];
    }
    delete[] waveforms;
    waveforms = tmp;

}