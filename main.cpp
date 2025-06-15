#include <iostream>
#include "PlayerManager.h"
#include "Game.h"
#include "GameManager.h"
int main() {
    PlayerManager pm("players.json");
    pm.loadPlayers();

    // إنشاء لاعبين جديدين
    Player player1 = {"pass123", "ahmed@email.com"};
    Player player2 = {"sara456", "sara@email.com"};

    pm.getPlayers()["ahmed"] = player1;
    pm.getPlayers()["sara"] = player2;

    // إنشاء مباراة جديدة
    Game game("ahmed", "sara");
    game.addMove({"ahmed", 0, 0});
    game.addMove({"sara", 1, 1});
    game.addMove({"ahmed", 0, 1});
    game.addMove({"sara", 2, 2});
    game.addMove({"ahmed", 0, 2}); // Ahmed wins

    game.setWinner("ahmed");

    // تحديث الإحصائيات
    pm.updateStats(game);
    pm.savePlayers();

    // طباعة معلومات اللاعبين
    for (const auto& [name, p] : pm.getPlayers()) {
        std::cout << "\nPlayer: " << name
                  << "\nEmail: " << p.email
                  << "\nWins: " << p.wins
                  << "\nLosses: " << p.losses
                  << "\nTies: " << p.ties << "\n";
    }

    // إنشاء GameManager واستخدامه
    GameManager gm("games.json", pm);
    gm.saveGame(game);       // حفظ اللعبة
    gm.replayGame(game);     // إعادة تشغيل اللعبة

    // تجربة البحث عن لاعب
    std::cout << "\nSearching for player sara...\n";
    if (pm.searchPlayer("sara")) {
        std::cout << "Player sara found.\n";
    }

    // تجربة التحقق من كلمة المرور
    if (pm.searchAndAssert("ahmed", "pass13")) {
        std::cout << "Password for ahmed is correct.\n";
    } else {
        std::cout << "Password check failed.\n";
    }

    // تجربة التحقق من البريد الإلكتروني
    if (pm.findAndCheckEmail("sara", "sara@email.com")) {
        std::cout << "Email for sara is correct.\n";
    } else {
        std::cout << "Email check failed.\n";
    }

    // حذف سجل المباريات للاعب
    pm.deletePlayerHistory("sara");
    std::cout << "\nSara's match history deleted.\n";

    return 0;
}
