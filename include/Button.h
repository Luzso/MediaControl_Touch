

class Button {
    public:

    Button(void (*btnCallback)() = nullptr, int x, int y, int width, int height);
    void pressed();

    private:

    void (*btnPressCallback)() = nullptr;
    void setBtnCallback(void (*btnCallBack)());
    void setPosition(int x, int y);
    void setDimensions(int width, int height);
    
    int x = 0;
    int y = 0;
    int touchWidth = 0;
    int touchHeight = 0;
    
};