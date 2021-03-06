/*
    Copyright (C) 2016-19 Sebastian J. Wolf

    This file is part of Wunderfitz.

    Wunderfitz is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    Wunderfitz is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Wunderfitz. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CURIOSITY_H
#define CURIOSITY_H

#include <QObject>
#include <QSettings>
#include "cloudapi.h"
#include "wagnis/wagnis.h"

class Curiosity : public QObject
{
    Q_OBJECT
public:
    explicit Curiosity(QObject *parent = 0);
    Q_INVOKABLE QString getTemporaryDirectoryPath();
    Q_INVOKABLE void removeTemporaryFiles();
    Q_INVOKABLE void captureRequested(const int &orientation, const int &viewfinderDimension, const int &offset);
    Q_INVOKABLE void captureCompleted(const QString &path);
    Q_INVOKABLE QString getSourceLanguage();
    Q_INVOKABLE void setSourceLanguage(const QString &sourceLanguage);
    Q_INVOKABLE QString getTargetLanguage();
    Q_INVOKABLE void setTargetLanguage(const QString &targetLanguage);
    Q_INVOKABLE bool getUseCloud();
    Q_INVOKABLE void setUseCloud(const bool &useCloud);
    Q_INVOKABLE QString getTranslatedText();

    CloudApi *getCloudApi();
    Wagnis *getWagnis();

signals:
    void translationSuccessful(const QString &text);
    void translationError(const QString &errorMessage);
    void ocrProgress(const int &percentCompleted);
    void ocrError(const QString &errorMessage);
    void ocrSuccessful();

public slots:
    void handleTranslationSuccessful(const QJsonArray &result);
    void handleTranslationError(const QString &errorMessage);
    void handleOcrProcessingSuccessful(const QString &fileName, const QJsonObject &result);    
    void handleOcrProcessingError(const QString &fileName, const QString &errorMessage);
    void handleOcrProcessingStatus(const QString &fileName, qint64 bytesSent, qint64 bytesTotal);

private:
    int captureOrientation;
    int captureOffset;
    int captureViewfinderDimension;
    QString capturePath;
    QString translatedText;
    QSettings settings;
    CloudApi *cloudApi;

    QNetworkAccessManager *networkAccessManager;
    Wagnis *wagnis;

    void processCapture();

};

#endif // CURIOSITY_H
