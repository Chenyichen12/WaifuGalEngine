#include <QGuiApplication>

#include "game.h"
#include "imageprovider.h"
#include "presets/basicaction.h"
#include "presets/basicmotion.h"
#include "stage.h"
#include "textbar.h"
#include <QQmlContext>
#include <QQmlEngine>
#include <QtQuick/QQuickView>

int main(int argc, char **argv) {
  QGuiApplication app(argc, argv);

  auto scene = new GalEngine::Game();
  auto provider = new GalEngine::ImageProvider(QQmlImageProviderBase::Image);
  provider->addCharacter("nike_normal", QImage(":/testimage/nike_normal.png"));
  provider->addCharacter("nike_kunhuo", QImage(":/testimage/nike_kunhuo.png"));
  provider->addCharacter("nike_zhihui", QImage(":/testimage/nike_zhihui.png"));

  // characters
  auto yichen1 =
      GalEngine::Character("image://character/stand/nike_normal", {});
  yichen1.transform.opacity = 0;
  auto yichen2 =
      GalEngine::Character("image://character/stand/nike_kunhuo", {});
  yichen2.transform.opacity = 0;
  auto yichen3 =
      GalEngine::Character("image://character/stand/nike_zhihui", {});
  yichen3.transform.opacity = 0;
  // pre add is fine
  scene->show(yichen1);
  scene->show(yichen2);
  scene->show(yichen3);

  *scene << new GalEngine::TextAction(
                {"Hello World!\nThis is yichen desu!", "yichen"})
         << new GalEngine::FadeInAction(yichen1.imageUrl, yichen1.transform,
                                        500)
         << new GalEngine::TextAction("Test change expression desu!")
         << new GalEngine::ChangeCharacterAction(yichen1, yichen2)
         << new GalEngine::TextAction(
                "Test change expression in animation desu!")
         << new GalEngine::ChangeCharacterAction(yichen2, yichen3, 50)
         << new GalEngine::TextAction("Test shake desu!")
         << new GalEngine::OneShakeAction(yichen3.imageUrl, yichen3.transform,
                                          100);

  QQuickView view;
  view.engine()->rootContext()->setContextProperty("game", scene);
  view.engine()->rootContext()->setContextProperty("textBar", scene->textBar());
  view.engine()->rootContext()->setContextProperty("stage", scene->stage());

  view.setResizeMode(QQuickView::SizeRootObjectToView);
  view.engine()->addImageProvider("character", provider);
  view.setSource(QUrl("qrc:///qml/main.qml"));
  view.show();

  scene->moveNext();

  return QGuiApplication::exec();
}