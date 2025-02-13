# 梅花易数占卜程序
# 包含基本卦象生成和变卦计算功能

# 先天八卦对应表（数字、卦名、符号、五行、卦象）
BAGUA = {
    1: {"name": "乾", "symbol": "☰", "nature": "天", "elements": [1, 1, 1]},
    2: {"name": "兑", "symbol": "☱", "nature": "泽", "elements": [1, 1, 0]},
    3: {"name": "离", "symbol": "☲", "nature": "火", "elements": [1, 0, 1]},
    4: {"name": "震", "symbol": "☳", "nature": "雷", "elements": [1, 0, 0]},
    5: {"name": "巽", "symbol": "☴", "nature": "风", "elements": [0, 1, 1]},
    6: {"name": "坎", "symbol": "☵", "nature": "水", "elements": [0, 1, 0]},
    7: {"name": "艮", "symbol": "☶", "nature": "山", "elements": [0, 0, 1]},
    8: {"name": "坤", "symbol": "☷", "nature": "地", "elements": [0, 0, 0]},
}

def find_gua(elements):
    """根据爻组合查找对应的卦"""
    for num in BAGUA:
        if BAGUA[num]["elements"] == elements:
            return num
    raise ValueError("未找到对应的卦")

def print_gua(name, shang, xia):
    """打印卦象信息"""
    print(f"{name}：")
    print(f"上卦：{BAGUA[shang]['nature']}{BAGUA[shang]['name']} {BAGUA[shang]['symbol']}")
    print(f"下卦：{BAGUA[xia]['nature']}{BAGUA[xia]['name']} {BAGUA[xia]['symbol']}")
    print(f"卦象：{BAGUA[shang]['symbol']}{BAGUA[xia]['symbol']}")
    print(f"组合：{BAGUA[shang]['nature']}上{BAGUA[xia]['nature']}下\n")

def calculate():
    """主计算函数"""
    try:
        # 获取输入
        num1 = int(input("请输入上卦数字（可输入任意整数）："))
        num2 = int(input("请输入下卦数字（可输入任意整数）："))
        num3 = int(input("请输入动爻数字（可输入任意整数）："))

        # 计算卦数（余数处理）
        shang_num = num1 % 8 or 8
        xia_num = num2 % 8 or 8
        dong_yao = num3 % 6 or 6  # 动爻位置（1-6）

        # 获取主卦信息
        main_shang = BAGUA[shang_num]
        main_xia = BAGUA[xia_num]

        # 生成主卦爻组合
        main_yao = main_xia["elements"] + main_shang["elements"]

        # 计算变爻
        main_yao[dong_yao-1] = 1 - main_yao[dong_yao-1]  # 阴阳转换

        # 分解变卦
        new_xia_num = find_gua(main_yao[:3])
        new_shang_num = find_gua(main_yao[3:])

        # 显示结果
        print("\n=== 占卜结果 ===")
        print_gua("本卦", shang_num, xia_num)
        print_gua("变卦", new_shang_num, new_xia_num)
        print(f"动爻位置：第{dong_yao}爻（从下往上数）")

        # 简单卦辞提示
        print("\n卦辞提示：")
        print("1. 本卦代表当前状态，变卦代表发展趋势")
        print("2. 需结合动爻位置综合分析卦象变化")
        print("3. 建议参考《周易》对应卦爻辞进行解读")

    except ValueError:
        print("输入无效，请确保输入的是整数")

if __name__ == "__main__":
    print("梅花易数占卜程序")
    print("----------------")
    print("使用方法：")
    print("1. 随意输入三个数字（如生日、时间等）")
    print("2. 前两个数字生成本卦，第三个数字确定动爻")
    print("3. 程序会自动计算并显示本卦和变卦\n")
    
    while True:
        calculate()
        if input("\n是否继续占卜？(y/n) ").lower() != 'y':
            break