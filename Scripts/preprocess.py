import pandas as pd
from pathlib import Path

INPUT_FILE = Path("../Data/2026-09-04.csv")
OUTPUT_FILE = Path("../Data/foods.csv")


def preprocess_food_data():
    # 1. 원본 CSV 읽기
    df = pd.read_csv(INPUT_FILE)

    # 2. 음식 하나당 하나의 행이 되도록 그룹화
    grouped = df.groupby("음식코드_1", sort=False)

    foods = []

    for food_id, group in grouped:
        # 음식 자체의 정보
        first = group.iloc[0]

        # 3. 재료 정보 만들기
        ingredients = []

        for _, row in group.iterrows():
            ingredient_name = row["국문식품명"]
            amount = row["중량"]

            # 결측값이 있는 재료는 제외
            if pd.isna(ingredient_name):
                continue

            # 중량이 없는 경우
            if pd.isna(amount):
                ingredients.append(str(ingredient_name))
            else:
                ingredients.append(
                    f"{ingredient_name}:{amount}"
                )

        # 4. 재료들을 하나의 문자열로 결합
        ingredient_text = "|".join(ingredients)

        # 5. 최종 Food 데이터 생성
        food = {
            "foodId": food_id,
            "foodName": first["음식 명"],
            "category": first["음식 대분류"],
            "subcategory": first["음식 중분류"],
            "weight": first["식품 중량"],
            "recipe": first["조리법 요약정보"],
            "allergyInfo": first["알레르기정보"],
            "ingredients": ingredient_text,
            "imageUrl": first["이미지주소"]
        }

        foods.append(food)

    # 6. DataFrame 생성
    result = pd.DataFrame(foods)

    # 7. 결측값을 빈 문자열로 변경
    result = result.fillna("")

    # 8. foods.csv 생성
    result.to_csv(
        OUTPUT_FILE,
        index=False,
        encoding="utf-8-sig"
    )

    print(f"전처리 완료: {OUTPUT_FILE}")
    print(f"원본 행 수: {len(df)}")
    print(f"음식 수: {len(result)}")


if __name__ == "__main__":
    preprocess_food_data()