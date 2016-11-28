#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTime>
#include "textured_rect.hpp"
#include "star.hpp"


#include <array>

class GameWindow;

QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)
QT_FORWARD_DECLARE_CLASS(QOpenGLShader)
QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT
public:
  GLWidget(GameWindow* mw, QColor const & background);
  ~GLWidget();

protected:
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void initializeGL() override;

  void Update(float elapsedSeconds);
  void Render();

  void mousePressEvent(QMouseEvent * e) override;
  void mouseDoubleClickEvent(QMouseEvent * e) override;
  void mouseMoveEvent(QMouseEvent * e) override;
  void mouseReleaseEvent(QMouseEvent * e) override;
  void wheelEvent(QWheelEvent * e) override;
  void keyPressEvent(QKeyEvent * e) override;
  void keyReleaseEvent(QKeyEvent * e) override;

private:
  int L2D(int px) const { return px * devicePixelRatio(); }

  GameWindow * m_mainWindow;

  unsigned int m_frames = 0;
  QTime m_time;
  QColor m_background;
  QSize m_screenSize;
  int static const m_starQuantity=10;
  int static const m_coordQuantity=2;
  int m_stars[m_starQuantity][m_coordQuantity];
  int m_phases[m_starQuantity];
  QOpenGLTexture * m_texture = nullptr;
  QOpenGLTexture * m_starTexture = nullptr;
  QOpenGLTexture * m_gunTexture = nullptr;
  TexturedRect * m_texturedRect = nullptr;
  Star * m_star = nullptr;
  QVector2D m_position = QVector2D(200, 200);
  bool m_directions[4] = { false, false, false, false };
};
