/*
 * Copyright (C) 2016 ~ 2018 Deepin Technology Co., Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef TTBCONTENT_H
#define TTBCONTENT_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include "controller/viewerthememanager.h"
//#include <dlistwidget.h>
//#include <DListWidget>
#include <DListWidget>
#include <DSpinner>
//#include <DtkWidgets>
//#include "dlistwidget.h"
#include <QListWidget>
#include <DListView>
#include <QAbstractItemModel>
#include <QStandardItem>
#include "controller/dbmanager.h"
#include <DAnchors>
#include <dimagebutton.h>
#include <DThumbnailProvider>
#include <QPropertyAnimation>
#include <QHBoxLayout>
#include <DIconButton>
#include <DBlurEffectWidget>
#include <DGuiApplicationHelper>
#include <DLabel>
#include "iconbutton.h"
DWIDGET_USE_NAMESPACE


class PushButton;
class ReturnButton;
class ElidedLabel;
class QAbstractItemModel;
//class DImageButton;
class ImageButton;
class MyImageListWidget;

class MyImageListWidget : public DWidget
{
    Q_OBJECT
public:
    MyImageListWidget(QWidget *parent = 0);
    bool ifMouseLeftPressed();
    void setObj(QObject *obj);
protected:
    bool eventFilter(QObject *obj, QEvent *e) Q_DECL_OVERRIDE;
signals:
    void mouseLeftReleased();
private:
    bool bmouseleftpressed = false;
    QObject *m_obj = nullptr;
    QPoint m_prepoint;
};
class ImageItem : public DLabel
{
    Q_OBJECT
public:
    ImageItem(int index = 0, QString path = NULL, char *imageType = NULL, QWidget *parent = 0);
    void setIndexNow(int i)
    {
        _indexNow = i;

    }
    void setPic(QImage image)
    {
//      _image->setPixmap(QPixmap::fromImage(image.scaled(60,50)));
    }
    void updatePic(QPixmap pixmap)
    {
        _pixmap = pixmap;
        update();
    }
signals:
    void imageItemclicked(int index, int indexNow);
protected:
    void mouseReleaseEvent(QMouseEvent *ev) override
    {
        bmouserelease = true;
    }
    void mousePressEvent(QMouseEvent *ev) override
    {
        bmouserelease = false;
        QEventLoop loop;
        QTimer::singleShot(200, &loop, SLOT(quit()));
        loop.exec();
        if (bmouserelease)
            emit imageItemclicked(_index, _indexNow);
    }
    void paintEvent(QPaintEvent *event) override;
private:
    int _index;
    int _indexNow = -1;
    DLabel *_image = nullptr;
    QString _path;
    QPixmap _pixmap;
    DSpinner *m_spinner;
    QString m_pixmapstring;
    bool bmouserelease = false;

};
class TTBContent : public QLabel
{
    Q_OBJECT
public:
    explicit TTBContent(bool inDB, DBImgInfoList m_infos, QWidget *parent = nullptr);

signals:
    void clicked();
    void imageClicked(int index, int addIndex);
    void resetTransform(bool fitWindow);
    void rotateClockwise();
    void rotateCounterClockwise();

    void removed();
    void imageEmpty(bool v);
    void contentWidthChanged(int width);
    void showPrevious();
    void showNext();

public slots:
    void setCurrentDir(QString text);
    void setImage(const QString &path, DBImgInfoList infos);
    void updateCollectButton();
    void slotTheme(bool theme);
    void setAdaptButtonChecked(bool flag);
    void disCheckAdaptImageBtn();
    void checkAdaptImageBtn();
    //heyi test 接收到信号之后更改隐藏标志符号
    void onChangeHideFlags(bool bFlags);

private slots:
    void onThemeChanged(ViewerThemeManager::AppTheme theme);
    void updateFilenameLayout();

protected:
    void resizeEvent(QResizeEvent *event);

private:
#ifndef LITE_DIV
    PushButton *m_folderBtn;
    ReturnButton *m_returnBtn;
#endif
    bool m_inDB;

    DIconButton *m_adaptImageBtn {nullptr};
    DIconButton *m_adaptScreenBtn {nullptr};
//    DIconButton* m_clBT;
    DIconButton *m_rotateLBtn {nullptr};
    DIconButton *m_rotateRBtn {nullptr};
    DIconButton *m_trashBtn {nullptr};
    DIconButton *m_preButton {nullptr};
    DIconButton *m_nextButton {nullptr};
//    ImageIconButton  *btPre = nullptr;
//    ImageIconButton  *btNext = nullptr;
//    ImageIconButton  *btAdapt = nullptr;
//    ImageIconButton  *btFit = nullptr;
//    ImageIconButton  *btLeft = nullptr;
//    ImageIconButton  *btRight = nullptr;
//    ImageIconButton  *btTrash = nullptr;
    ElidedLabel *m_fileNameLabel;
    DWidget *m_imgList;
    QHBoxLayout *m_imglayout;
//    DWidget *m_imgListView;
    MyImageListWidget *m_imgListView;
    DWidget *m_imgListView_prespc;
    DWidget *m_imgListView_spc;
    DWidget *m_preButton_spc;
    DWidget *m_nextButton_spc;
    DBImgInfoList m_imgInfos ;
    QString m_imagePath;
    int m_windowWidth;
    int m_contentWidth;
    int m_lastIndex = 0;
    int m_nowIndex = 0;
    int m_imgInfos_size = 0;
    int m_startAnimation = 0;
    bool bresized = true;
    bool badaptImageBtnChecked = false;
    bool badaptScreenBtnChecked = false;
    //heyi test
    bool m_bIsHide = false;
};

#endif // TTLCONTENT_H
