//============================================================================
// ファイル名: Time.h
// 役割: ゲーム全体の「時間」を管理するクラスの宣言（設計図）
//============================================================================
#pragma once

#include <chrono>

// ゲーム全体の時間を管理する静的クラス(インスタンス化はしない)
class Time {
private:
    //========================================================================
    // 内部計算用：chrono型(chronoライブラリ特有の型)の時間記録変数
    // c++が新しければインクルード先で名前衝突を避けるため、inlineにしておくと良い
    //========================================================================

    // 変数宣言
    // std::chrono::high_resolution_clock::time_point : そのプラットフォームでの最も短い間隔のクロック
    static std::chrono::high_resolution_clock::time_point startTime; //ゲーム開始時の絶対時間
    static std::chrono::high_resolution_clock::time_point prevTime;  //前のフレームの絶対時間

    //========================================================================
    // 実際に使う時間データ
    //========================================================================
    static float deltaTime;             // 1フレームの経過時間(timeScaleの影響を受ける)
    static float unscaledDeltaTime;     // 1フレームの経過時間(timeScaleの影響を受けない)
    static float time;                  // ゲーム開始からの総経過時間(秒、timeScaleの影響を受ける)
    static float realtimeSinceStartup;  // 現実の総経過時間(秒、timeScaleの影響を受けない)
    static float timeScale;             // 時間の倍率(1.0=通常, 0.5=スロー, 0.0=停止)
    static int frameCount;              // これまでに描画した(処理した)総フレーム数

    static float sceneTime;             // 現在のステージ(シーン)が始まってからのゲーム内経過時間

    static float maximumDeltaTime;      // 経過時間の上限値(スパイク対策用の値)
    static float fixedDeltaTime;        // 物理演算用の固定時間

    //========================================================================
    // スムーズ補正用バッファ(直近5フレームの履歴を保存)
    //========================================================================
    static constexpr int SAVE_FRAME_MAX = 5;        // 履歴を保存する最大フレーム数
    static float deltaTimeBuffer[SAVE_FRAME_MAX];   // 直近のdeltaTimeを保存するバッファ
    static int saveFrameIndex;      // バッファの現在書き込み位置を示すインデックス
    static float smoothDeltaTime;   // 直近のdeltaTimeの平均値から計算された、滑らかな経過時間

    //========================================================================
    // FPS(1秒間の描画回数)計算用
    //========================================================================
    static int fpsCount;            // 1秒間に何回Updateが呼ばれたか数えるカウンタ
    static float fpsTimer;          // 1秒を測るためのストップウォッチ用タイマー
    static float currentFPS;        // 計算結果(現在のFPS)

    // コンストラクタを private にしてインスタンス化を禁止
    // Time timer; のように「Timeクラスの実体(インスタンス)」を作られないように、
    // コンストラクタ(初期化処理)をprivateに隠して使用禁止にする
    Time() = default;

    //! @brief コピーコンストラクタを削除
    Time(const Time&) = delete;

    //! @brief 代入演算子を削除
    Time& operator=(const Time&) = delete;

public:

    //========================================================================
    // ゲッター(ReadOnly)
    //========================================================================

    //! @brief 前のフレームからの経過時間を取得します
    //! @return 経過時間(秒単位、timeScaleの影響を受けます)
    inline static float GetDeltaTime() { return deltaTime; }

    //! @brief 前のフレームからの経過時間を取得します
    //! @return 経過時間(秒単位、timeScaleの影響を受けず常に現実の時間と同じ)
    inline static float GetUnscaledDeltaTime() { return unscaledDeltaTime; }

    //! @brief ゲーム開始からのゲーム内の総経過時間を取得します
    //! @return 総経過時間(秒単位、ポーズ時は停止)
    inline static float GetTime() { return time; }

    //! @brief ゲーム開始からの現実の総経過時間を取得します
    //! @return 総経過時間(秒単位、ポーズ時も進行)
    static float GetRealtimeSinceStartup() { return realtimeSinceStartup; }

    //! @brief ゲーム開始からこれまでに処理された総フレーム数を取得します
    //! @return 総フレーム数
    inline static int   GetFrameCount() { return frameCount; }

    //! @brief 現在の時間の進む速さ(倍率)を取得します
    //! @return タイムスケール(1.0で通常)
    inline static float GetTimeScale() { return timeScale; }

    //! @brief 現在のFPS(1秒間の描画回数)を取得します
    //! @return FPSの値
    inline static float GetFPS() { return currentFPS; }

    //! @brief スパイク対策の上限値を取得します
    //! @return 経過時間の上限値(秒単位)
    static float GetMaximumDeltaTime() { return maximumDeltaTime; }

    //! @brief 物理演算用の固定時間(秒)を取得します
    //! @return　固定時間(秒単位)
    static float GetFixedDeltaTime() { return fixedDeltaTime; }

    //! @brief 直近数フレームで平均化された、滑らかな経過時間を取得します
    //! @return　滑らかな経過時間(秒単位)
    static float GetSmoothDeltaTime() { return smoothDeltaTime; }

    //! 現在のステージ(シーン)が始まってからの経過時間を取得します
    //! @return ステージの経過時間(秒単位、ポーズ中は停止)
    static float GetSceneTime() { return sceneTime; }

    //========================================================================
    // セッター
    //========================================================================
    //! @brief 時間の進む速さ(時間の倍率)を設定します
    //! @param scale 倍率(1.0で通常、0.5でスロー、0.0で停止。0未満は0に補正される)
    inline static void SetTimeScale(float scale) {
        // もしマイナスの時間(時間が逆戻りする)が設定されそうになったら、
        // バグを防ぐために強制的に0.0(停止)する
        if (scale < 0.0f) {
            scale = 0.0f;
        }
        timeScale = scale;
    }

    //! @brief スパイク対策の上限値を設定します(デフォルト0.1秒)
    //! @param maxDelta 上限値(秒単位)
    static void SetMaximumDeltaTime(float maxDelta) {
        maximumDeltaTime = maxDelta;
    }

    //! @brief 物理演算用の固定時間を設定します(デフォルトは約60FPSの0.0166f)
    //! @param fixedDelta 固定時間(秒単位)
    static void SetFixedDeltaTime(float fixedDelta) {
        fixedDeltaTime = fixedDelta;
    }

    //========================================================================
    // システム関数
    //========================================================================

    //! @brief 時間管理システムを初期化する
    //! @brief メインループに入る前に1回だけ呼び出す
    static void Initialize();

    //! @brief 時間を更新し、経過時間などを再計算する
    //! @brief メインループの中で、毎フレームの最初に必ず呼び出す
    static void Update();

    //! @brief ステージ(シーン)の経過時間をゼロにリセットする
    //! @brief ステージが切り替わった瞬間に呼び出す
    static void ResetSceneTime();

};