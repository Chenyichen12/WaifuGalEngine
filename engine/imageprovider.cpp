#include "imageprovider.h"
namespace GalEngine {
ImageProvider::ImageProvider(ImageType type, Flags flags)
    : QQuickImageProvider(type, flags) {}

void ImageProvider::addCharacter(const QString &nameUrl, QImage image) {
  Q_ASSERT(!assets.contains(nameUrl));
  assets.insert(nameUrl, image);
}

QImage ImageProvider::requestImage(const QString &id, QSize *size,
                                   const QSize &requestedSize) {
  auto idList = id.split('/');
  Q_ASSERT(idList.size() == 2);

  if(idList.first() == icon_name){
    // icon 
    return assets[idList[1]];
  }
  if(idList.first() == stand_name){
    // stand
    return assets[idList[1]];
  }

  Q_ASSERT(false);
}
} // namespace GalEngine