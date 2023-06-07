#pragma once
class Texture :public Singleton<Texture>
{
private:
    struct TextureNode
    {
        ID3D11ShaderResourceView*   srv; //ÀÚ¿ø
        Int2                        textureSize;
    };

    //    first     second
    //    key       value
    map<wstring, TextureNode> textureList;

public:
    ~Texture();
    ID3D11ShaderResourceView* LoadTexture(wstring file);
    bool DeleteTexture(wstring file);
    Int2 GetTextureSize(wstring file);
};

