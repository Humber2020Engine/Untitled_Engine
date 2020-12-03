#include "Sprite.h"
#include "../../Core/CoreEngine.h"
#include "../../Graphics/TextureHandler.h"
#include "GameObject.h"

std::vector<Vertex> Sprite::boxCoords = std::vector<Vertex>();
std::vector<Vertex> Sprite::boxCoordsRev = std::vector<Vertex>();



Sprite::Sprite(GLuint shaderProgram_, const std::string& textureName_, GameObject * parent_) : depth(0), 
spriteSize(glm::vec2(0))
{
    parent = parent_;
    shaderProgram = shaderProgram_;
    textureName = textureName_;

    tint = glm::vec4(1.0f);

    //If the box coords dont exist already make them.

    if (boxCoords.size() == 0) {
        boxCoords.reserve(4);
        boxCoords.push_back(Vertex());
        boxCoords.push_back(Vertex());
        boxCoords.push_back(Vertex());
        boxCoords.push_back(Vertex());


        boxCoords[0].position = glm::vec2(0.0f, 1.0f);
        boxCoords[0].texCoords = glm::vec2(0, 0);

        boxCoords[1].position = glm::vec2(1.0f, 1.0f);
        boxCoords[1].texCoords = glm::vec2(1, 0);

        boxCoords[2].position = glm::vec2(0.0f, 0.0f);
        boxCoords[2].texCoords = glm::vec2(0, 1);

        boxCoords[3].position = glm::vec2(1.0f, 0.0f);
        boxCoords[3].texCoords = glm::vec2(1, 1);
    }

    if (boxCoordsRev.size() == 0) {
        boxCoordsRev.reserve(4);
        boxCoordsRev.push_back(Vertex());
        boxCoordsRev.push_back(Vertex());
        boxCoordsRev.push_back(Vertex());
        boxCoordsRev.push_back(Vertex());


        boxCoordsRev[0].position = glm::vec2(1.0f, 1.0f);
        boxCoordsRev[0].texCoords = glm::vec2(0, 0);

        boxCoordsRev[1].position = glm::vec2(0.0f, 1.0f);
        boxCoordsRev[1].texCoords = glm::vec2(1, 0);

        boxCoordsRev[2].position = glm::vec2(1.0f, 0.0f);
        boxCoordsRev[2].texCoords = glm::vec2(0, 1);

        boxCoordsRev[3].position = glm::vec2(0.0f, 0.0f);
        boxCoordsRev[3].texCoords = glm::vec2(1, 1);
    }

    TextureHandler::GetInstance()->InitTexture(textureName_);

    spriteSize = glm::vec2(TextureHandler::GetInstance()->GetTextureData(textureName_)->spriteWidth,
        TextureHandler::GetInstance()->GetTextureData(textureName_)->spriteHeight);
    textureID = TextureHandler::GetInstance()->GetTextureData(textureName)->textureID;

    box = BoundingBox(spriteSize, glm::vec2(0));


    InitRenderData();
}

Sprite::~Sprite()
{
    parent = nullptr;
}

BoundingBox Sprite::GetBoundingBox()
{
    return box;
}


GLuint Sprite::GetShaderProgram() const
{
    return shaderProgram;
}

glm::vec2 Sprite::GetDimensions() const
{
    return spriteSize;
}

glm::vec2 Sprite::GetScale() const
{
    return scale;
}

bool Sprite::GetFlip() const
{
    return flip;
}

void Sprite::SetScale(glm::vec2 scale_)
{
    scale = spriteSize * scale_;
}

void Sprite::Draw(Camera* camera_)
{
    glUniform1f(textureID, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glm::mat4 transform = glm::mat4(1.0f);

    transform = glm::translate(transform, glm::vec3(parent->GetPosition(), 0));

    transform = glm::translate(transform, glm::vec3(0.5f * scale.x, 0.5f * scale.y, 0.0f)); // move origin of rotation to center of quad
    transform = glm::rotate(transform, glm::radians(-parent->GetRotation()), glm::vec3(0.0f, 0.0f, 1.0f)); // rotate
    transform = glm::translate(transform, glm::vec3(-0.5f * scale.x, -0.5f * scale.y, 0.0f)); // move origin back

    transform = glm::scale(transform, glm::vec3(scale, 0));

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetOrthographic()));

    //if (useView) {
    //    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
    //}

    glUniform4fv(color, 1, glm::value_ptr(tint));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

}

void Sprite::SetFlip(bool flip_)
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    if (!flip_) {
        glBufferData(GL_ARRAY_BUFFER, boxCoords.size() * sizeof(Vertex), &boxCoords[0], GL_STATIC_DRAW);
    }
    else {
        glBufferData(GL_ARRAY_BUFFER, boxCoordsRev.size() * sizeof(Vertex), &boxCoordsRev[0], GL_STATIC_DRAW);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    flip = flip_;
}


void Sprite::InitRenderData()
{
    // configure VAO/VBO

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, boxCoords.size() * sizeof(Vertex), &boxCoords[0], GL_STATIC_DRAW);

    //POSITION
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

    //TEXTURE COORDINATES
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    modelLoc = glGetUniformLocation(shaderProgram, "model");
    projLoc = glGetUniformLocation(shaderProgram, "projection");
    color = glGetUniformLocation(shaderProgram, "spriteColor");
}
