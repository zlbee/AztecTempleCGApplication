#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class temple {
public:

private:
    void draw();

};

int step_num = 4;

// bind textures   
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, base1_texBuffer);
glUniform1i(glGetUniformLocation(simpleShader.ID, "texture"), 0);

// uniform: mvp
simpleShader.setMat4("projection", projection);
simpleShader.setMat4("view", view);
simpleShader.setMat4("model", model);

// transform m: scale the first base
glm::mat4 base1Model = glm::translate(model, glm::vec3(0.0f, 1.732051f, 0.0f));
simpleShader.setMat4("model", base1Model);
// draw the first base
glBindVertexArray(base1_vao);
glDrawArrays(GL_TRIANGLES, 0, 36);

// transform: first base steps
glm::mat4 step1Model;
step1Model = glm::translate(base1Model, glm::vec3(0.0f, -1.732051f, 18.0f));
step1Model = glm::rotate(step1Model, glm::radians(120.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
step1Model = glm::translate(step1Model, glm::vec3(0.0f, 0.0f, -4.0f / step_num / 2));
//step1Model1 = step1Model;
for (int i = 1; i < step_num + 1; i++)
{
    glm::mat4 step1Model_temp = step1Model;
    step1Model_temp = glm::translate(step1Model, glm::vec3(0.0f, 0.0f, 4.0f / step_num * i));
    step1Model_temp = glm::rotate(step1Model_temp, glm::radians(120.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    step1Model_temp = glm::scale(step1Model_temp, glm::vec3(4.0f, 3.464101615f / step_num, 2.0f / step_num));
    simpleShader.setMat4("model", step1Model_temp);
    // draw the first base step
    glBindVertexArray(cube_vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

// transform: left enclosure for the first base
glm::mat4 enclosure1Model;
enclosure1Model = glm::translate(base1Model, glm::vec3(2.0f, 0.0f, 17.0f));
enclosure1Model = glm::rotate(enclosure1Model, glm::radians(240.0f), glm::vec3(1.0f, 0.0f, 0.0f));
enclosure1Model = glm::translate(enclosure1Model, glm::vec3(0.0f, -0.433013f, 0.0f));
enclosure1Model = glm::scale(enclosure1Model, glm::vec3(0.1f, 1.0f, 1.0f));
simpleShader.setMat4("model", enclosure1Model);
// draw the enclosure
glBindVertexArray(enclosure_vao);
glDrawArrays(GL_TRIANGLES, 0, 36);

// transform: right enclosure for the first base
glm::mat4 enclosure2Model;
enclosure2Model = glm::translate(base1Model, glm::vec3(-2.0f, 0.0f, 17.0f));
enclosure2Model = glm::rotate(enclosure2Model, glm::radians(240.0f), glm::vec3(1.0f, 0.0f, 0.0f));
enclosure2Model = glm::translate(enclosure2Model, glm::vec3(0.0f, -0.433013f, 0.0f));
enclosure2Model = glm::scale(enclosure2Model, glm::vec3(0.1f, 1.0f, 1.0f));
simpleShader.setMat4("model", enclosure2Model);
// draw the enclosure
glBindVertexArray(enclosure_vao);
glDrawArrays(GL_TRIANGLES, 0, 36);

// transform m: scale the second base
glm::mat4 base2Model = transform(base1Model, glm::vec3(1.0f), glm::vec3(0.0f, 3.464102f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.0f);
simpleShader.setMat4("model", base2Model);
// draw the second base
glBindVertexArray(base2_vao);
glDrawArrays(GL_TRIANGLES, 0, 36);

// transform: left enclosure for the first base
glm::mat4 enclosure3Model;
enclosure3Model = glm::translate(base2Model, glm::vec3(2.0f, 0.0f, 13.0f));
enclosure3Model = glm::rotate(enclosure3Model, glm::radians(240.0f), glm::vec3(1.0f, 0.0f, 0.0f));
enclosure3Model = glm::translate(enclosure3Model, glm::vec3(0.0f, -0.433013f, 0.0f));
enclosure3Model = glm::scale(enclosure3Model, glm::vec3(0.1f, 1.0f, 1.0f));
simpleShader.setMat4("model", enclosure3Model);
// draw the enclosure
glBindVertexArray(enclosure_vao);
glDrawArrays(GL_TRIANGLES, 0, 36);

// transform: right enclosure for the first base
glm::mat4 enclosure4Model;
enclosure4Model = glm::translate(base2Model, glm::vec3(-2.0f, 0.0f, 13.0f));
enclosure4Model = glm::rotate(enclosure4Model, glm::radians(240.0f), glm::vec3(1.0f, 0.0f, 0.0f));
enclosure4Model = glm::translate(enclosure4Model, glm::vec3(0.0f, -0.433013f, 0.0f));
enclosure4Model = glm::scale(enclosure4Model, glm::vec3(0.1f, 1.0f, 1.0f));
simpleShader.setMat4("model", enclosure4Model);
// draw the enclosure
glBindVertexArray(enclosure_vao);
glDrawArrays(GL_TRIANGLES, 0, 36);

// transform m: scale the third base
glm::mat4 base3Model = transform(base2Model, glm::vec3(1.0f), glm::vec3(0.0f, 3.464102f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.0f);
simpleShader.setMat4("model", base3Model);
// draw the third base
glBindVertexArray(base3_vao);
glDrawArrays(GL_TRIANGLES, 0, 36);

// transform: left enclosure for the third base
glm::mat4 enclosure5Model;
enclosure5Model = glm::translate(base3Model, glm::vec3(2.0f, 0.0f, 9.0f));
enclosure5Model = glm::rotate(enclosure5Model, glm::radians(240.0f), glm::vec3(1.0f, 0.0f, 0.0f));
enclosure5Model = glm::translate(enclosure5Model, glm::vec3(0.0f, -0.433013f, 0.0f));
enclosure5Model = glm::scale(enclosure5Model, glm::vec3(0.1f, 1.0f, 1.0f));
simpleShader.setMat4("model", enclosure5Model);
// draw the enclosure
glBindVertexArray(enclosure_vao);
glDrawArrays(GL_TRIANGLES, 0, 36);

// transform: right enclosure for the first base
glm::mat4 enclosure6Model;
enclosure6Model = glm::translate(base3Model, glm::vec3(-2.0f, 0.0f, 9.0f));
enclosure6Model = glm::rotate(enclosure6Model, glm::radians(240.0f), glm::vec3(1.0f, 0.0f, 0.0f));
enclosure6Model = glm::translate(enclosure6Model, glm::vec3(0.0f, -0.433013f, 0.0f));
enclosure6Model = glm::scale(enclosure6Model, glm::vec3(0.1f, 1.0f, 1.0f));
simpleShader.setMat4("model", enclosure6Model);
// draw the enclosure
glBindVertexArray(enclosure_vao);
glDrawArrays(GL_TRIANGLES, 0, 36);