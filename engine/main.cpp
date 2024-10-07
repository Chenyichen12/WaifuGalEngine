#include <QGuiApplication>

#include "game.h"
#include "imageprovider.h"
#include "presets/basicaction.h"
#include "presets/basicmotion.h"

#include <QQmlContext>
#include <QQmlEngine>
#include <QtQuick/QQuickView>

#include "choiceview.h"
#include "stage.h"
#include "textbar.h"

int main(int argc, char **argv) {
  QGuiApplication app(argc, argv);

  auto scene = new GalEngine::Game();
  auto provider =
      new GalEngine::CharacterImageProvider(QQmlImageProviderBase::Image);
  provider->addCharacter("nike_normal", QImage(":/testimage/nike_normal.png"));
  provider->addCharacter("nike_kunhuo", QImage(":/testimage/nike_kunhuo.png"));
  provider->addCharacter("nike_zhihui", QImage(":/testimage/nike_zhihui.png"));

  // characters
  auto yichen1 = GalEngine::Character("image://character/stand/nike_normal",
                                      GalEngine::CharacterTransform().fade(0));
  auto yichen2 = GalEngine::Character("image://character/stand/nike_kunhuo",
                                      GalEngine::CharacterTransform().fade(0));
  auto yichen3 = GalEngine::Character("image://character/stand/nike_zhihui",
                                      GalEngine::CharacterTransform().fade(0));
  // pre add is fine
  scene->show(yichen1);
  scene->show(yichen2);
  scene->show(yichen3);

  *scene
      << new GalEngine::FadeInAction(yichen1.imageUrl, yichen1.transform, 500)
      << new GalEngine::TextAction(
             {"Hello World!\nThis is yichen desu!", "yichen"})
      << new GalEngine::ChangeCharacterAction(yichen1, yichen2)
      << new GalEngine::TextAction("Test change expression desu!")
      << new GalEngine::ChangeCharacterAction(yichen2, yichen3, 50)
      << new GalEngine::TextAction("Test change expression in animation desu!")
      << new GalEngine::OneShakeAction(yichen3.imageUrl, yichen3.transform, 100)
      << new GalEngine::TextAction("Test shake desu!")
      << new GalEngine::GoToAction("choice 1")

      << new GalEngine::LabelAction("choice 1")
      << new GalEngine::TextAction("You should go block 1 desu")
      << new GalEngine::GoToAction("merge")

      << new GalEngine::LabelAction("choice 2")
      << new GalEngine::TextAction("You should not go choice 2 desu")

      << new GalEngine::LabelAction("merge")
      << new GalEngine::TextAction("Merge desu!");

  auto choice1 = new GalEngine::ChoiceAction();
  choice1->addChoice("Hello", "choice1-1")
      .addChoice("You should see choice here", "choice1-2")
      .addChoice("Amazing desu", "choice1-3");
  *scene << choice1 << new GalEngine::LabelAction("choice1-1")
         << new GalEngine::TextAction("You choose Hello desu!")
         << new GalEngine::GoToAction("merge")
         << new GalEngine::LabelAction("choice1-2")
         << new GalEngine::TextAction("You choose choice 2 desu!")
         << new GalEngine::GoToAction("merge")
         << new GalEngine::LabelAction("choice1-3")
         << new GalEngine::TextAction("You choose Amazing desu!")
         << new GalEngine::GoToAction("merge");


  QQuickView view;
  view.engine()->rootContext()->setContextProperty("game", scene);
  view.engine()->rootContext()->setContextProperty("textBar", scene->textBar());
  view.engine()->rootContext()->setContextProperty("stage", scene->stage());
  view.engine()->rootContext()->setContextProperty("choiceView",
                                                   scene->choiceView());

  view.setResizeMode(QQuickView::SizeRootObjectToView);
  view.engine()->addImageProvider("character", provider);
  view.setSource(QUrl("qrc:///qml/main.qml"));
  view.show();

  scene->moveNext();

  return QGuiApplication::exec();
}