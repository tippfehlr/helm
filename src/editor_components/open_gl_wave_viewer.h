/* Copyright 2013-2017 Matt Tytel
 *
 * helm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * helm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with helm.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#ifndef OPEN_GL_WAVE_VIEWER_H
#define OPEN_GL_WAVE_VIEWER_H

#include "JuceHeader.h"

#include "helm_common.h"
#include "open_gl_component.h"

class OpenGlWaveViewer : public OpenGlComponent, public SliderListener {
  public:
    OpenGlWaveViewer(int resolution);
    virtual ~OpenGlWaveViewer();

    void setWaveSlider(Slider* slider);
    void setAmplitudeSlider(Slider* slider);
    void drawRandom();
    void drawSmoothRandom();
    void resetWavePath();
    void sliderValueChanged(Slider* sliderThatWasMoved) override;

    void paintBackground();
    void paintPositionImage();
    void resized() override;
    void mouseDown(const MouseEvent& e) override;

    void showRealtimeFeedback(bool show_feedback) override;

  protected:
    void init() override;
    void render() override;
    void destroy() override;

    void drawPosition();
  
  private:
    float phaseToX(float phase);

    Slider* wave_slider_;
    Slider* amplitude_slider_;
    mopo::Output* wave_phase_;
    mopo::Output* wave_amp_;
    Path wave_path_;
    int resolution_;

    Image position_image_;
    OpenGLTexture position_texture_;
    ScopedPointer<OpenGLShaderProgram::Uniform> texture_;

    float* position_vertices_;
    int* position_triangles_;
    GLuint vertex_buffer_;
    GLuint triangle_buffer_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OpenGlWaveViewer)
};

#endif // OPEN_GL_WAVE_VIEWER_H