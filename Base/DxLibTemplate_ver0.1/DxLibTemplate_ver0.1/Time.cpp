#include "Time.h"

//-----------------------------------------------------
// static変数の実体定義
//-----------------------------------------------------
std::chrono::high_resolution_clock::time_point Time::startTime;
std::chrono::high_resolution_clock::time_point Time::prevTime;

float Time::deltaTime = 0.0f;
float Time::unscaledDeltaTime = 0.0f;
float Time::time = 0.0f;
float Time::realtimeSinceStartup = 0.0f;
float Time::timeScale = 1.0f;
int Time::frameCount = 0;

float Time::sceneTime = 0.0f;

float Time::maximumDeltaTime = 0.1f;
float Time::fixedDeltaTime = 0.016666f; // 1.0f / 60.0f に相当(60FPS)
float Time::deltaTimeBuffer[Time::SAVE_FRAME_MAX] = { 0.0f };
int Time::saveFrameIndex = 0;
float Time::smoothDeltaTime = 0.0f;

int Time::fpsCount = 0;
float Time::fpsTimer = 0.0f;
float Time::currentFPS = 0.0f;


//-----------------------------------------------------
// 関数の実装
//-----------------------------------------------------


//-----------------------------------------------------
// 初期化処理
//-----------------------------------------------------
void Time::Initialize() {
    // 現在のPCの時間を取得し、開始時間としてセットする
    auto now = std::chrono::high_resolution_clock::now();
    startTime = now;
    prevTime = now;

    // 変数をすべて初期状態にリセット
    deltaTime = 0.0f;
    unscaledDeltaTime = 0.0f;
    time = 0.0f;
    realtimeSinceStartup = 0.0f;

    timeScale = 1.0f;
    frameCount = 0;

    // ステージ時間をゼロにする
    sceneTime = 0.0f;

    // 履歴バッファのクリア
    for (int i = 0; i < SAVE_FRAME_MAX; ++i) {
        deltaTimeBuffer[i] = 0.0f;
    }
    saveFrameIndex = 0;
    smoothDeltaTime = 0.0f;

    fpsCount = 0;
    fpsTimer = 0.0f;
    currentFPS = 0.0f;
}

//-----------------------------------------------------
// 更新処理
//-----------------------------------------------------
void Time::Update() {
    // 今この瞬間の時間を取得する
    auto currentTime = std::chrono::high_resolution_clock::now();

    // 前のフレームからの経過時間を計算する
    // duration: 時間間隔の型
    std::chrono::duration<float> diff = currentTime - prevTime;
    // 秒に変換された小数が手に入る
    unscaledDeltaTime = diff.count();

    // 現実の総経過時間を計算(PCの時計基準)
    std::chrono::duration<float> totalDiff = currentTime - startTime;
    realtimeSinceStartup = totalDiff.count();

    // 異常値の防止
    // ウィンドウを掴んだりしてゲームが数秒間フリーズした直後、
    // 経過時間が3.0秒などの巨大な数値になり、キャラクターが壁をすり抜けるのを防ぐ
    // (最大でもmaximumDeltaTime分しか進まないように上限をかけておく)
    // スパイク(フレーム時間や通信(PING)の瞬間的な急上昇)時の安全機構
    if (maximumDeltaTime < unscaledDeltaTime) {
        unscaledDeltaTime = maximumDeltaTime;
    }

    // タイムスケールの適用
    // 経過時間に倍率を掛ける(timeScaleが0.5なら、deltaTimeは半分になる＝スローモーション)
    deltaTime = unscaledDeltaTime * timeScale;

    // 総経過時間の更新
    // ゲーム開始時から今までの時間を計算する
    // (毎フレームのdeltaTimeを足すことで、スローや停止を反映)
    time += deltaTime;

    // 毎フレームの経過時間をステージ時間に蓄積する
    // (deltaTimeを足しているので、Scaleを弄って
    // ポーズ中やスロー中っぽくしてもその挙動に沿った形になる)
    sceneTime += deltaTime;

    // smoothDeltaTimeの計算(移動平均)
    deltaTimeBuffer[saveFrameIndex] = deltaTime;
    // 配列をループさせるリングバッファ
    saveFrameIndex = (saveFrameIndex + 1) % SAVE_FRAME_MAX; 

    // 配列の中身を足していく
    float sum = 0.0f;
    for (int i = 0; i < SAVE_FRAME_MAX; ++i) {
        sum += deltaTimeBuffer[i];
    }

    // 平均値を算出
    smoothDeltaTime = sum / SAVE_FRAME_MAX;

    // フレームカウントを1増やす
    frameCount++;

    // 次の計算のために、今の時間を前の時間として保存しておく
    prevTime = currentTime;

    // FPSの計算処理
    // カウントを増やす
    fpsCount++;
    // 現実の経過時間をストップウォッチに足す
    fpsTimer += unscaledDeltaTime;
    // もしストップウォッチが1秒(1.0f)を超えたら
    if (1.0f <= fpsTimer) {
        // この1秒間に何回カウントされたかをFPSとして記録する
        // (正確に出すため、経過時間で割っている)
        currentFPS = static_cast<float>(fpsCount) / fpsTimer;

        // 次の1秒を測るために、カウントとストップウォッチをリセットする
        fpsCount = 0;
        fpsTimer = 0.0f;
    }
}

//-----------------------------------------------------
// ステージ(シーン時間のリセット)
//-----------------------------------------------------
void Time::ResetSceneTime() {
    sceneTime = 0.0f;
}