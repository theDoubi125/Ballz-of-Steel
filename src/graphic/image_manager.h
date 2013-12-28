#ifndef IMAGE_MANAGER_H_INCLUDED
#define IMAGE_MANAGER_H_INCLUDED

class ImageManager
{
public:
    ~ImageManager();
    void loadImage(std::string path, std::string name);
    sf::Texture* getTexture(std::string name);
    void setTexture(sf::Sprite sprite, std::string name);
    static ImageManager instance;

private:
    ImageManager();
    std::map<std::string, sf::Texture*> m_images;
    std::vector<std::string> m_textNames;
};

#endif // IMAGE_MANAGER_H_INCLUDED
